#pragma once

#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace CraftWorld {
	class Connection;

	class Server {
			friend Connection;

			boost::asio::io_context ioContext_;

			tcp::acceptor acceptor_;

		public:
			// The server will listen on the specified port
			Server();

			/**
			 * Starts the Server.
			 * Create a socket and initiate an asynchronous accept operation that waits for new connections.
			 */
			void run();
	};
}
