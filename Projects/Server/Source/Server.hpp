#pragma once

#include <memory>
#include <boost/asio.hpp>
#include <boost/mpi/communicator.hpp>

#include "World.hpp"
#include "Connection.hpp"

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

			/**
			 * The communicator which allows communication with other MPI processes.
			 */
			boost::mpi::communicator communicator_;

			/**
			 * The game world.
			 */
			World world_;

			/**
			 * The currently open connections, associated to the username of the player on that connection.
			 */
			std::vector<std::shared_ptr<Connection>> connections_;

			/**
			 * The amount of matchmaker servers that are in use.
			 */
			int matchmakerCount_;

			/**
			 * Prints the specified message to the console.
			 * @param message The message to print.
			 */
			void print(const std::string& message);

			/**
			 * Starts listening for new connections.
			 */
			void startListening();

		public:
			/**
			 * Creates a new Server.
			 * @param matchmakerCount The amount of matchmaker servers to run.
			 * @param port The port to listen on for new Connections. This will only affect matchmaker servers and can be left unspecified for other servers.
			 * @param worldChunkSize The amount of chunks in the world.
			 * @param chunkBlockSize The amount of blocks in a chunk.
			 */
			explicit Server(const int& matchmakerCount, const int& port = -1, const Utility::Vector3D<int>& worldChunkSize = { 4, 4, 4 }, const Utility::Vector3D<int>& chunkBlockSize = { 4, 4, 4 });

			/**
			 * Makes the class polymorphic.
			 */
			~Server() = default;

			/**
			 * Starts the Server.
			 * Create a socket and initiate an asynchronous accept operation that waits for new Connections.
			 */
			void run();

			/**
			 * Determines if this Server is a matchmaker.
			 * @return Whether this Server is a matchmaker.
			 */
			bool isMatchmaker() const;

			/**
			 * Determines if this Server is the creator of the World.
			 * @return Whether this Server is the creator.
			 */
			bool isCreator() const;
	};
}
