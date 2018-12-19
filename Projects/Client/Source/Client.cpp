#include "Client.hpp"

#include <iterator>
#include <iostream>
#include <boost/serialization/shared_ptr.hpp>

#include "Actions/ConnectAction.hpp"
#include "World.hpp"

namespace CraftWorld {
	Client::Client(const std::string& host, const int& port) : socket_(
		[&]() {
			// Initialize IO context
			boost::asio::io_context ioContext;

			// Resolve server endpoint
			tcp::resolver::results_type endpoints = tcp::resolver(ioContext).resolve(host, std::to_string(port));

			// Create new socket
			tcp::socket socket(ioContext);

			// Establish a connection
			try {
				boost::asio::connect(socket, endpoints);
			} catch(std::exception& e) {
				std::cerr << e.what() << std::endl;

				exit(1);
			}

			return socket;
		}()
	) {
	}

	void Client::run() {
		send(std::make_shared<Actions::ConnectAction>(-1, username_));

		while(true) {
			// Receive data
			std::string data;
			boost::system::error_code errorCode;
			size_t length = boost::asio::read_until(socket_, boost::asio::dynamic_buffer(data), "\n\n", errorCode);
			data = data.substr(0, length - 2);

			// Check if data was received
			if(errorCode == boost::asio::error::eof) {
				// The connection was closed, so exit
				exit(0);
			} else if(errorCode) {
				// An error occurred
				throw boost::system::system_error(errorCode);
			}

			// Handle data
			std::cout << "Received data: " << std::endl << data << std::endl;

			auto refreshWorldAction = std::static_pointer_cast<Actions::RefreshWorldAction>(Utility::Serialization::fromString(data));

			// Get world
			auto world = refreshWorldAction->world;

			// Randomly choose function:
			switch(rand() % 13) {
				//Move action
				case 0: //Send action moveNorth;
					send(std::make_shared<Actions::MoveAction>(-1, Actions::MoveAction::NORTH));
					break;

				case 1: //Send action moveEast;
					send(std::make_shared<Actions::MoveAction>(-1, Actions::MoveAction::EAST));
					break;

				case 2: //Send action moveSouth;
					send(std::make_shared<Actions::MoveAction>(-1, Actions::MoveAction::SOUTH));
					break;

				case 3: //Send action moveWest;
					send(std::make_shared<Actions::MoveAction>(-1, Actions::MoveAction::WEST));
					break;

				case 4: //Send action standStill
					// Do nothing
					break;

					//Remove block actions
				case 5: //Send action removeBlockNorth;
					send(std::make_shared<Actions::PickUpBlockAction>(-1, Actions::PickUpBlockAction::NORTH));
					break;

				case 6: //Send action removeBlockEast;
					send(std::make_shared<Actions::PickUpBlockAction>(-1, Actions::PickUpBlockAction::EAST));
					break;

				case 7: //Send action removeBlockSouth;
					send(std::make_shared<Actions::PickUpBlockAction>(-1, Actions::PickUpBlockAction::SOUTH));
					break;

				case 8: //Send action removeBlockWest;
					send(std::make_shared<Actions::PickUpBlockAction>(-1, Actions::PickUpBlockAction::WEST));
					break;

					//Add block actions
				case 9:  //Send action addBlockNorth;
					send(std::make_shared<Actions::PlaceBlockAction>(-1, Actions::PlaceBlockAction::NORTH));
					break;

				case 10: //Send action addBlockEast;
					send(std::make_shared<Actions::PlaceBlockAction>(-1, Actions::PlaceBlockAction::EAST));
					break;

				case 11: //Send action addBlockSouth;
					send(std::make_shared<Actions::PlaceBlockAction>(-1, Actions::PlaceBlockAction::SOUTH));
					break;

				case 12: //Send action addBlockWest;
					send(std::make_shared<Actions::PlaceBlockAction>(-1, Actions::PlaceBlockAction::WEST));
					break;
			}
		}
	}
}
