#pragma once

#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

namespace CraftWorld {
	class Server;

	class Connection :
		public boost::enable_shared_from_this<Connection> {
			friend Server;

			tcp::socket socket_;

			// Handles the rest of the client connection
			void handleWrite(const boost::system::error_code& error, size_t bytes_transferred);

			void send(const std::string& message) const;

		public:
			Connection(Server& server);

			// Handle the client (currently just sends "Hello world!")
			void start();
	};
}
