#include "Server.hpp"

#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/mpi/collectives.hpp>
#include <Actions/LocatePlayerAction.hpp>

#include "Connection.hpp"
#include "Chunk.hpp"
#include "Actions/Action.hpp"
#include "Actions/LocatePlayerAction.hpp"

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

		// Start the IO context
		if(isMatchmaker()) {
			// Only the matchmakers will use TCP connections
			ioContext_.run();
		}
	}

	void Server::print(const std::string& message) {
		std::cout << "[" << communicator_.rank() << "/" << communicator_.size() << " - " << (isCreator()
			? "Creator"
			: (isMatchmaker()
				? "Matchmaker"
				: "Slave")) << "] " << message << std::endl;
	}

	void Server::startListening() {
		acceptor_.async_accept(
			// Create a new lambda which asynchronously handles the client request and calls run again to start accepting new connections
			[&](const boost::system::error_code& error, tcp::socket socket) {
				if(!error) {
					// Open a new connection on the current socket
					auto connection = Connection(std::move(socket), *this);

					// Add the connection to the list of open connections
					connections_.push_back(connection);

					// Start the connection
					connection.start();
				}

				// Listen for other new connections
				startListening();
			}
		);
	}

	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wmissing-noreturn"

	void Server::run() {
		if(isMatchmaker()) {
			startListening();
		}

		// Start main loop
		for(;;) {
			// Synchronize updates between servers
			communicator_.barrier();

			// Check for incoming requests from other servers
			std::shared_ptr<Actions::Action> action;
			communicator_.irecv(boost::mpi::any_source, 0, action);

			if(action != nullptr) {
				print("Received action: " + action->name);

				if(dynamic_cast<Actions::LocatePlayerAction*>(action.get())) {
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
											print("Found player!");
										}
									}
								}
							);
						}
					);
				}
			}

			// Update world
			world_.update();
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
