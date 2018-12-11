#pragma once

#include <string>
#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace CraftWorld {
	class Server;

	class Connection :
		public std::enable_shared_from_this<Connection> {
			friend Server;

			tcp::socket socket_;

			std::string message_;

			// Handles the rest of the client connection
			void handleWrite(const boost::system::error_code& error, size_t bytes_transferred);

			void send(const std::string& message);

		public:
			Connection(Server& server);

			// Handle the client (currently just sends "Hello world!")
			void start();
	};
}
