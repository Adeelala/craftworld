#pragma once

#include <string>
#include <boost/asio.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <thread>
#include <unistd.h>

#include "Utility/Serialization.hpp"

using boost::asio::ip::tcp;

namespace CraftWorld {
	/**
	 * Used to connect to, and exchange data with, a Server.
	 */
	class Client {
			/**
			 * The socket used to transmit data.
			 */
			tcp::socket socket_;
			std::string username_="Steve";

			template<typename ActionType>
			void send(const ActionType& action) {
				boost::system::error_code error;
				boost::asio::write(socket_, boost::asio::buffer(Utility::Serialization::toString(action) + "\n\n"), error);
			}

		public:
			/**
			 * Creates a new Client.
			 * @param host The host of the Server to connect to.
			 * @param port The port of the Server to connect to.
			 */
			Client(const std::string& host, const int& port);

			/**
			 * Starts communication with the Server.
			 * @param dataHandler The function that will handle incoming data.
			 */
			void run();
	};
}
