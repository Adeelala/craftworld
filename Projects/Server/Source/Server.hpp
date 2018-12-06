#pragma once

#include <boost/asio.hpp>

#include "Connection.hpp"

using boost::asio::ip::tcp;

namespace CraftWorld {
	class Server {
		public:
			// The server will listen on the specified port
			Server(boost::asio::io_context& io_context);

		private:
			// Create a socket and initiate an asynchronous accept operation that waits for new connections
			void start_accept();

			// Asynchronously handles the client request and calls start_accept again to start accepting new connections
			void handle_accept(Connection::pointer new_connection, const boost::system::error_code& error);

			tcp::acceptor acceptor_;
	};
}
