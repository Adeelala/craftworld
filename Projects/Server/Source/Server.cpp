#include "Server.hpp"

#include "Connection.hpp"

namespace CraftWorld {
	Server::Server() : acceptor_(ioContext_, tcp::endpoint(tcp::v4(), 8000)) {
	}

	void Server::run() {
		std::shared_ptr<Connection> connection = std::make_shared<Connection>(Connection(*this));

		acceptor_.async_accept(
			connection->socket_,

			// Create a new lambda which asynchronously handles the client request and calls run again to start accepting new connections
			[&](const boost::system::error_code& error) {
				if(!error) {
					connection->start();
				}

				run();
			}
		);

		ioContext_.run();
	}
}
