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
	Connection::Connection(Server& server) : socket_(server.acceptor_.get_executor().context()), server_(server) {
	}

	void Connection::receive() {
		boost::asio::async_read_until(
			socket_,
			boost::asio::dynamic_buffer(receiveMessage_),
			"\n\n",
			[&](const boost::system::error_code& errorCode, std::size_t length) {
				std::lock_guard<std::mutex> lock(server_.mutex_);

				if(!errorCode) {
					// Process incoming messages
					auto action = server_.fromString(receiveMessage_.substr(0, receiveMessage_.size() - 2));

					// Get the action that needs to be executed
					if(action != nullptr) {
						server_.print("Received connection action: " + action->name);

						if(action->name == "ConnectAction") {
							// New client connection
							auto connectAction = std::static_pointer_cast<Actions::ConnectAction>(action);

							// Set the username
							username_ = connectAction->username;

							// Locate the server that has the player
							for(int rank = 0; rank < server_.communicator_.size(); ++rank) {
								server_.print("Locating player: " + connectAction->username);

								server_.send(std::make_shared<Actions::LocatePlayerAction>(server_.communicator_.rank(), connectAction->username), rank);
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
		std::lock_guard<std::mutex> lock(server_.mutex_);

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
		server_.print("Made a connection!");

		receive();
	}
}
