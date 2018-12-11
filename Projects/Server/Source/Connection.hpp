#pragma once

#include <string>
#include <memory>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace CraftWorld {
	class Server;

	/**
	 * A connection between the Client and the Server, used to exchange data.
	 */
	class Connection :
		public std::enable_shared_from_this<Connection> {
			friend Server;

			/**
			 * The socket used for communication.
			 */
			tcp::socket socket_;

			/**
			 * The message to send.
			 */
			std::string message_;

			/**
			 * Handles writes by the CLient.
			 * @param error The error that occurred.
			 * @param bytesTransferred The amount of bytes that were transferred.
			 */
			void handleWrite(const boost::system::error_code& error, size_t bytesTransferred);

			/**
			 * Sends a new message to the Client.
			 * @param message The message to send.
			 */
			void send(const std::string& message);

		public:
			/**
			 * Creates a new Connection.
			 * @param server The Server to use for the Connection.
			 */
			Connection(Server& server);

			/**
			 * Starts the Connection.
			 */
			void start();
	};
}
