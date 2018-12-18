#include "Server.hpp"

#include <set>
#include <string>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/mpi/collectives.hpp>
#include <unistd.h>
#include <thread>

#include "Chunk.hpp"
#include "Actions/Action.hpp"
#include "Actions/LocatePlayerAction.hpp"
#include "Actions/FoundPlayerAction.hpp"
#include "Actions/RefreshWorldAction.hpp"
#include "Actions/GetWorldAction.hpp"

namespace CraftWorld {
	Server::Server(const int& matchmakerCount, const int& port, const Utility::Vector3D<int>& worldChunkSize, const Utility::Vector3D<int>& chunkBlockSize) : matchmakerCount_(matchmakerCount), acceptor_(ioContext_, tcp::endpoint(tcp::v4(), port)), world_({ worldChunkSize.x / communicator_.size(), worldChunkSize.y, worldChunkSize.z }, chunkBlockSize) {
		if(isMatchmaker()) {
			print("Listening on port " + std::to_string(port));
		}

		World world;
		if(isCreator()) {
			print("Generating world...");

			// Create world
			world = World::generate(worldChunkSize, chunkBlockSize);

			print("World size: " + static_cast<std::string>(world.getSize()));

			print("Generated world");
			print("Scattering world...");
		}

		print("Waiting for " + static_cast<std::string>(world_.getSize()) + " chunks");

		boost::mpi::scatter(communicator_, world.entities, world_.entities.data(), world_.entities.size(), 0);

		if(isCreator()) {
			print("Scattered world");
		}
		print("Received world");

		print("Local chunk count: " + static_cast<std::string>(world_.getSize()));
	}

	void Server::print(const std::string& message) {
		std::cout << "[" << communicator_.rank() << "/" << communicator_.size() << " - " << (isCreator()
			? "Creator"
			: (isMatchmaker()
				? "Matchmaker"
				: "Slave")) << "] " << message << std::endl;
	}

	void Server::startListening() {
		print("Listening for new connections...");

		// Open a new connection on the current socket
		auto connection = std::make_shared<Connection>(*this);

		// Add the connection to the list of open connections
		connections_.push_back(connection);

		acceptor_.async_accept(
			connection->socket_,

			// Create a new lambda which asynchronously handles the client request and calls run again to start accepting new connections
			[&](const boost::system::error_code& error) {
				print("New incoming connection");

				if(!error) {
					// Start the connection
					connection->start();
				}

				// Listen for other new connections
				startListening();
			}
		);

		// Only the matchmakers will use TCP connections
		ioContext_.run();
	}

	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wmissing-noreturn"

	void Server::run() {
		std::thread(
			[&] {
				if(isMatchmaker()) {
					startListening();
				}
			}
		).detach();

		// Start main loop
		for(;;) {
			print("Executing main loop...");

			// Synchronize updates between servers
			communicator_.barrier();

			// Request game state from all servers that have active players
			if(isMatchmaker()) {
				std::set<int> serversToRefresh;
				for(auto& connection : connections_) {
					if(connection->serverRank_ >= 0) {
						serversToRefresh.insert(connection->serverRank_);
					}
				}
				for(auto& rank : serversToRefresh) {
					communicator_.isend(rank, 0, std::make_shared<Actions::Action>(Actions::GetWorldAction(std::to_string(communicator_.rank()))));
				}
			}

			// Check for incoming requests from other servers
			std::shared_ptr<Actions::Action> action;
			communicator_.irecv(boost::mpi::any_source, 0, action);

			if(action != nullptr) {
				print("Received action: " + action->name);

				if(action->name == "LocatePlayerAction") {
					auto locatePlayerAction = std::static_pointer_cast<Actions::LocatePlayerAction>(action);

					// We need to locate a player, so search our world and see if we have that player
					world_.forEach(
						[&](auto& chunk) {
							chunk->forEach(
								[&](auto& entity) {
									if(dynamic_cast<Entities::Player*>(entity.get())) {
										auto player = std::static_pointer_cast<Entities::Player>(entity);

										if(player->username == locatePlayerAction->username) {
											// Found the player!
											print("Found player: " + locatePlayerAction->username);
											communicator_.isend(std::stoi(locatePlayerAction->source), 0, std::make_shared<Actions::FoundPlayerAction>(std::to_string(communicator_.rank()), locatePlayerAction->username));
										}
									}
								}
							);
						}
					);
				} else if(action->name == "FoundPlayerAction") {
					auto foundPlayerAction = std::static_pointer_cast<Actions::FoundPlayerAction>(action);

					// We found the player, notify the corresponding connection
					for(auto& connection : connections_) {
						if(connection->username_ == foundPlayerAction->username) {
							connection->serverRank_ = std::stoi(foundPlayerAction->source);
						}
					}
				} else if(action->name == "GetWorldAction") {
					auto getWorldAction = std::static_pointer_cast<Actions::GetWorldAction>(action);

					// We need to send the world to the requester
					communicator_.isend(std::stoi(getWorldAction->source), 0, std::make_shared<Actions::RefreshWorldAction>(std::to_string(communicator_.rank()), world_));
				} else if(action->name == "RefreshWorldAction") {
					auto refreshWorldAction = std::static_pointer_cast<Actions::RefreshWorldAction>(action);

					// We received the world from a server, forward it to all clients
					for(auto& connection : connections_) {
						if(connection->serverRank_ == std::stoi(refreshWorldAction->source)) {
							// Serialize and send the world
							std::stringstream stringStream;
							boost::archive::text_oarchive archive(stringStream);
							archive << BOOST_SERIALIZATION_NVP(refreshWorldAction);

							connection->send(stringStream.str());
						}
					}
				}
			}

			// Update world
			world_.update();

			// Wait a second
			usleep(1000000);
		}
	}

	#pragma clang diagnostic pop

	bool Server::isMatchmaker() const {
		return communicator_.rank() < matchmakerCount_;
	}

	bool Server::isCreator() const {
		return communicator_.rank() == 0;
	}
}
