#pragma once

#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace CraftWorld {
	class Connection;

	/**
	 * Exchanges data with any connected Clients.
	 */
	class Server {
			friend Connection;

			/**
			 * The IO context to use.
			 */
			boost::asio::io_context ioContext_;

			/**
			 * The acceptor to use.
			 */
			tcp::acceptor acceptor_;

		public:
			/**
			 * Creates a new Server.
			 * @param port The port to listen on for new Connections.
			 */
			Server(const int& port);

			/**
			 * Starts the Server.
			 * Create a socket and initiate an asynchronous accept operation that waits for new connections.
			 */
			void run();
	};
}
