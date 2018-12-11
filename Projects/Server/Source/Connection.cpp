#include "Connection.hpp"

#include <iostream>
#include <sstream>
#include <boost/bind.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>

#include "Server.hpp"
#include "World.hpp"

namespace CraftWorld {
	Connection::Connection(Server& server) : socket_(server.acceptor_.get_executor().context()) {
	}

	void Connection::handleWrite(const boost::system::error_code& error, size_t bytes_transferred) {
	}

	void Connection::send(const std::string& message) {
		message_ = message + "\n\n";

		// Send message
		boost::asio::async_write(
			socket_,
			boost::asio::buffer(message_),
			boost::bind(
				&Connection::handleWrite,
				shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		);

		std::cout << "Sent data:" << std::endl << message_ << std::endl;
	}

	void Connection::start() {
		std::cout << "Made a connection!" << std::endl;

		// Create test world
		World world({ 1, 1, 1 }, { 1, 1, 1 });

		// Serialize World
		std::stringstream stringStream;
		boost::archive::xml_oarchive archive(stringStream);
		archive << BOOST_SERIALIZATION_NVP(world);

		// Send the message
		send(stringStream.str());
	}
}
