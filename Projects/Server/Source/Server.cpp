#include "Server.hpp"

#include <set>
#include <string>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/mpi/collectives.hpp>
#include <boost/optional.hpp>
#include <unistd.h>
#include <mpi.h>
#include <thread>

#include "Chunk.hpp"

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

	std::shared_ptr<Actions::Action> Server::receive() {
		std::string serializedAction;
		communicator_.recv(boost::mpi::any_source, 0, serializedAction);

		print("Received: " + serializedAction);

		if(serializedAction.empty()) {
			return nullptr;
		} else {
			return Utility::Serialization::fromString(serializedAction);
		}
	}

	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wmissing-noreturn"

	void Server::run() {
		// Start client <-> server event loop
		std::thread(
			[&] {
				if(isMatchmaker()) {
					startListening();
				}
			}
		).detach();

		// Start server <-> server event loop
		std::thread(
			[&] {
				for(;;) {
					// Check for incoming requests from other servers
					auto action = receive();

					std::lock_guard<std::mutex> lock(mutex_);

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

													send(std::make_shared<Actions::FoundPlayerAction>(communicator_.rank(), locatePlayerAction->username), locatePlayerAction->source);
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
									connection->serverRank_ = foundPlayerAction->source;

									print("Connected server " + std::to_string(connection->serverRank_) + " to player " + connection->username_);
								}
							}
						} else if(action->name == "GetWorldAction") {
							auto getWorldAction = std::static_pointer_cast<Actions::GetWorldAction>(action);

							print("Sending world to " + std::to_string(getWorldAction->source));

							// We need to send the world to the requester
							send(std::make_shared<Actions::RefreshWorldAction>(communicator_.rank(), world_), getWorldAction->source);
						} else if(action->name == "RefreshWorldAction") {
							auto refreshWorldAction = std::static_pointer_cast<Actions::RefreshWorldAction>(action);

							// We received the world from a server, forward it to all clients
							for(auto& connection : connections_) {
								if(connection->serverRank_ == refreshWorldAction->source) {
									// Serialize and send the world
									print("Sending refresh world action to " + connection->username_);

									connection->send(Utility::Serialization::toString(refreshWorldAction));
								}
							}
						} else if(action->name == "MoveAction") {
							auto moveAction = std::static_pointer_cast<Actions::MoveAction>(action);

							for(auto connection : connections_) {
								if(connection->serverRank_ == moveAction->source) {
									for(int chunkX = 0; chunkX < world_.entities.size(); ++chunkX) {
										for(int chunkY = 0; chunkY < world_.entities[chunkX].size(); ++chunkY) {
											for(int chunkZ = 0; chunkZ < world_.entities[chunkX][chunkY].size(); ++chunkZ) {
												auto& chunk = world_.entities[chunkX][chunkY][chunkZ];

												for(int blockX = 0; blockX < chunk->entities.size(); ++blockX) {
													for(int blockY = 0; blockY < chunk->entities[blockX].size(); ++blockY) {
														for(int blockZ = 0; blockZ < chunk->entities[blockX][blockY].size(); ++blockZ) {
															auto& entity = chunk->entities[blockX][blockY][blockZ];

															if(dynamic_cast<Entities::Player*>(entity.get())) {
																auto player = std::static_pointer_cast<Entities::Player>(entity);

																const Utility::Vector3D<int> coordinates = { blockX, blockY, blockZ };
																Utility::Vector3D<int> newCoordinates;

																switch(moveAction->direction) {
																	case Actions::MoveAction::NORTH:
																		newCoordinates = coordinates + Utility::Vector3D<int> { 0, 0, 1 };
																		break;

																	case Actions::MoveAction::EAST:
																		newCoordinates = coordinates + Utility::Vector3D<int> { 1, 0, 0 };
																		break;

																	case Actions::MoveAction::SOUTH:
																		newCoordinates = coordinates + Utility::Vector3D<int> { 0, 0, -1 };
																		break;

																	case Actions::MoveAction::WEST:
																		newCoordinates = coordinates + Utility::Vector3D<int> { -1, 0, 0 };
																		break;
																}

																if(newCoordinates.x >= 0 && newCoordinates.y >= 0 && newCoordinates.z >= 0 && newCoordinates.x < chunk->getSize().x && newCoordinates.y < (chunk->getSize().y - 1) && newCoordinates.z < chunk->getSize().z) {
																	print("Moving player " + player->username + " from " + static_cast<std::string>(coordinates) + " to " + static_cast<std::string>(newCoordinates));

																	chunk->swap(coordinates, newCoordinates);
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						} else if(action->name == "PickUpBlockAction") {
							auto pickUpBlockAction = std::static_pointer_cast<Actions::PickUpBlockAction>(action);

							for(auto connection : connections_) {
								if(connection->serverRank_ == pickUpBlockAction->source) {
									for(int chunkX = 0; chunkX < world_.entities.size(); ++chunkX) {
										for(int chunkY = 0; chunkY < world_.entities[chunkX].size(); ++chunkY) {
											for(int chunkZ = 0; chunkZ < world_.entities[chunkX][chunkY].size(); ++chunkZ) {
												auto& chunk = world_.entities[chunkX][chunkY][chunkZ];

												for(int blockX = 0; blockX < chunk->entities.size(); ++blockX) {
													for(int blockY = 0; blockY < chunk->entities[blockX].size(); ++blockY) {
														for(int blockZ = 0; blockZ < chunk->entities[blockX][blockY].size(); ++blockZ) {
															auto& entity = chunk->entities[blockX][blockY][blockZ];

															if(dynamic_cast<Entities::Player*>(entity.get())) {
																auto player = std::static_pointer_cast<Entities::Player>(entity);

																const Utility::Vector3D<int> coordinates = { blockX, blockY, blockZ };
																Utility::Vector3D<int> newCoordinates;

																switch(pickUpBlockAction->direction) {
																	case Actions::PickUpBlockAction::NORTH:
																		newCoordinates = coordinates + Utility::Vector3D<int> { 0, 0, 1 };
																		break;

																	case Actions::PickUpBlockAction::EAST:
																		newCoordinates = coordinates + Utility::Vector3D<int> { 1, 0, 0 };
																		break;

																	case Actions::PickUpBlockAction::SOUTH:
																		newCoordinates = coordinates + Utility::Vector3D<int> { 0, 0, -1 };
																		break;

																	case Actions::PickUpBlockAction::WEST:
																		newCoordinates = coordinates + Utility::Vector3D<int> { -1, 0, 0 };
																		break;
																}

																if(newCoordinates.x >= 0 && newCoordinates.y >= 0 && newCoordinates.z >= 0 && newCoordinates.x < chunk->getSize().x && newCoordinates.y < (chunk->getSize().y - 1) && newCoordinates.z < chunk->getSize().z) {
																	print("Picking up block from " + static_cast<std::string>(newCoordinates));

																	chunk->entities[newCoordinates.x][newCoordinates.y][newCoordinates.z] = std::make_shared<Entities::Block>(Entities::Block::AIR);
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						} else if(action->name == "PlaceBlockAction") {
							auto placeBlockAction = std::static_pointer_cast<Actions::PlaceBlockAction>(action);

							for(auto connection : connections_) {
								if(connection->serverRank_ == placeBlockAction->source) {
									for(int chunkX = 0; chunkX < world_.entities.size(); ++chunkX) {
										for(int chunkY = 0; chunkY < world_.entities[chunkX].size(); ++chunkY) {
											for(int chunkZ = 0; chunkZ < world_.entities[chunkX][chunkY].size(); ++chunkZ) {
												auto& chunk = world_.entities[chunkX][chunkY][chunkZ];

												for(int blockX = 0; blockX < chunk->entities.size(); ++blockX) {
													for(int blockY = 0; blockY < chunk->entities[blockX].size(); ++blockY) {
														for(int blockZ = 0; blockZ < chunk->entities[blockX][blockY].size(); ++blockZ) {
															auto& entity = chunk->entities[blockX][blockY][blockZ];

															if(dynamic_cast<Entities::Player*>(entity.get())) {
																auto player = std::static_pointer_cast<Entities::Player>(entity);

																const Utility::Vector3D<int> coordinates = { blockX, blockY, blockZ };
																Utility::Vector3D<int> newCoordinates;

																switch(placeBlockAction->direction) {
																	case Actions::PlaceBlockAction::NORTH:
																		newCoordinates = coordinates + Utility::Vector3D<int> { 0, 0, 1 };
																		break;

																	case Actions::PlaceBlockAction::EAST:
																		newCoordinates = coordinates + Utility::Vector3D<int> { 1, 0, 0 };
																		break;

																	case Actions::PlaceBlockAction::SOUTH:
																		newCoordinates = coordinates + Utility::Vector3D<int> { 0, 0, -1 };
																		break;

																	case Actions::PlaceBlockAction::WEST:
																		newCoordinates = coordinates + Utility::Vector3D<int> { -1, 0, 0 };
																		break;
																}

																if(newCoordinates.x >= 0 && newCoordinates.y >= 0 && newCoordinates.z >= 0 && newCoordinates.x < chunk->getSize().x && newCoordinates.y < (chunk->getSize().y - 1) && newCoordinates.z < chunk->getSize().z) {
																	print("Placing block at " + static_cast<std::string>(newCoordinates));

																	chunk->entities[newCoordinates.x][newCoordinates.y][newCoordinates.z] = std::make_shared<Entities::Block>(Entities::Block::DIRT);
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		).detach();

		// Start game loop
		for(;;) {
			{
				std::lock_guard<std::mutex> lock(mutex_);

				// Request game state from all servers that have active players
				if(isMatchmaker()) {
					print("Requesting game state from active servers");

					std::set<int> serversToRefresh;
					for(auto& connection : connections_) {
						if(connection->serverRank_ >= 0) {
							serversToRefresh.insert(connection->serverRank_);
						}
					}

					for(auto& rank : serversToRefresh) {
						send(std::make_shared<Actions::GetWorldAction>(communicator_.rank()), rank);
					}
				}

				print("Executing main loop...");

				// Synchronize updates between servers
				communicator_.barrier();

				// Update world
				world_.update();
			}

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
