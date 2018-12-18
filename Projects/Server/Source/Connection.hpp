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
			 * The message to receive.
			 */
			 std::string receiveMessage_;

			/**
			 * The message to send.
			 */
			std::string sendMessage_;

			/**
			 * The server.
			 */
			Server& server_;

			/**
			 * The username of the player connected to this server.
			 */
			std::string username_;

			/**
			 * The rank of the server that contains this player.
			 */
			int serverRank_ = -1;

			/**
			 * Asynchronously receives data.
			 */
			void receive();

			/**
			 * Sends a new message to the Client.
			 * @param message The message to send.
			 */
			void send(const std::string& message);

		public:
			/**
			 * Creates a new Connection.
			 * @param server The server.
			 */
			Connection(Server& server);

			/**
			 * Starts the Connection.
			 */
			void start();
	};
}
