#include "Connection.hpp"

#include <iostream>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

namespace CraftWorld::Server {
	boost::shared_ptr<Connection> Connection::create(boost::asio::io_context& io_context) {
		return pointer(new Connection(io_context));
	}

	tcp::socket& Connection::socket() {
		return socket_;
	}

	void Connection::start() {
		std::cout << "Made a connection!" << std::endl;
		message_ = "Hello world!";
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
