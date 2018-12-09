#include "Server.hpp"

#include <boost/bind.hpp>

#include "Connection.hpp"

namespace CraftWorld {
	Server::Server() : acceptor_(ioContext_, tcp::endpoint(tcp::v4(), 8000)) {
		ioContext_.run();
	}

	void Server::run() {
		std::shared_ptr<Connection> connection = std::make_shared<Connection>(new Connection(*this));

		acceptor_.async_accept(
			connection->socket_, boost::bind(
				// Create a new lambda which asynchronously handles the client request and calls run again to start accepting new connections
				[&](const std::shared_ptr<Connection>& connection, const boost::system::error_code& error) {
					if(!error) {
						connection->start();
					}

					run();
				},
				this,
				connection,
				boost::asio::placeholders::error
			)
		);
	}
}
