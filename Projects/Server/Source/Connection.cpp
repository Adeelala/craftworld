#include "Connection.hpp"

#include <iostream>
#include <sstream>
#include <utility>
#include <boost/bind.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "Server.hpp"
#include "World.hpp"
#include "Actions/Action.hpp"
#include "Actions/ConnectAction.hpp"
#include "Actions/LocatePlayerAction.hpp"

namespace CraftWorld {
	Connection::Connection(tcp::socket socket, Server& server) : socket_(std::move(socket)), server_(server) {
	}

	void Connection::receive() {
		boost::asio::async_read(
			socket_,
			boost::asio::buffer(receiveMessage_),
			[&](const boost::system::error_code& errorCode, std::size_t length) {
				if(!errorCode) {
					// Process incoming messages
					std::stringstream stringStream;
					stringStream << receiveMessage_;
					boost::archive::text_iarchive archive(stringStream);
					std::shared_ptr<Actions::Action> action;
					archive >> BOOST_SERIALIZATION_NVP(action);

					// Get the action that needs to be executed
					if(action != nullptr) {
						server_.print("Received connection action: " + action->name);

						if(dynamic_cast<Actions::ConnectAction*>(action.get())) {
							// New client connection
							auto connectAction = std::static_pointer_cast<Actions::ConnectAction>(action);

							// Set the username
							username_ = connectAction->username;

							// Locate the server that has the player
							for(int rank = 0; rank < server_.communicator_.size(); ++rank) {
								server_.print("Locating player: " + connectAction->username);

								server_.communicator_.isend(rank, 0, std::make_shared<Actions::Action>(Actions::LocatePlayerAction(std::to_string(server_.communicator_.rank()), connectAction->username)));
							}
						}
					}

					// Clear message
					receiveMessage_ = "";

					// Keep receiving messages
					receive();
				}
			}
		);
	}

	void Connection::send(const std::string& message) {
		sendMessage_ = message + "\n\n";

		// Send message
		boost::asio::async_write(
			socket_,
			boost::asio::buffer(sendMessage_),
			[&](const boost::system::error_code& errorCode, std::size_t length) {
				if(!errorCode) {
					server_.print("Sent data: " + sendMessage_);
				}
			}
		);
	}

	void Connection::start() {
		std::cout << "Made a connection!" << std::endl;

		receive();
		// Start connection loop
		//for(;;) {

		//}


		// Send the message
		//send(stringStream.str());
	}
}
