#include "Connection.hpp"

#include <iostream>
#include <sstream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>

#include "World.hpp"

namespace CraftWorld {
	boost::shared_ptr<Connection> Connection::create(boost::asio::io_context& io_context) {
		return pointer(new Connection(io_context));
	}

	tcp::socket& Connection::socket() {
		return socket_;
	}

	void Connection::start() {
		std::cout << "Made a connection!" << std::endl;

		// Create test world
		World world({ 16, 16, 16 }, { 16, 16, 16 });

		// Serialize World
		std::stringstream stringStream;
		boost::archive::text_oarchive archive(stringStream);
		world.serialize(archive);

		// Set message
		message_ = stringStream.str();

		// Send message
		boost::asio::async_write(
			socket_, boost::asio::buffer(message_), boost::bind(
				&Connection::handle_write,
				shared_from_this(),
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred
			)
		);
	}

	Connection::Connection(boost::asio::io_context& io_context) : socket_(io_context) {
	}

	void Connection::handle_write(const boost::system::error_code& error, size_t bytes_transferred) {
	}
}
