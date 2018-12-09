#include "Connection.hpp"

#include <iostream>
#include <sstream>
#include <boost/bind.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "Server.hpp"
#include "World.hpp"

namespace CraftWorld {
	Connection::Connection(Server& server) : socket_(server.ioContext_) {
	}

	void Connection::handleWrite(const boost::system::error_code& error, size_t bytes_transferred) {
	}

	void Connection::send(const std::string& message) const {
		// Send message
		boost::asio::async_write(
			socket_,
			boost::asio::buffer(message),
			boost::bind(
				&Connection::handleWrite,
				shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		);
	}

	void Connection::start() {
		std::cout << "Made a connection!" << std::endl;

		// Create test world
		World world({ 16, 16, 16 }, { 16, 16, 16 });

		// Serialize World
		std::stringstream stringStream;
		boost::archive::text_oarchive archive(stringStream);
		world.serialize(archive);

		// Send the message
		send(stringStream.str());
	}
}
