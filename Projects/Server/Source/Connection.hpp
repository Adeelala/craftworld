#pragma once

#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

namespace CraftWorld::Server {
	class Connection :
		public boost::enable_shared_from_this<Connection> {
		public:
			typedef boost::shared_ptr<Connection> pointer;

			static pointer create(boost::asio::io_context& io_context);

			tcp::socket& socket();

			// Handle the client (currently just sends "Hello world!")
			void start();

		private:
			Connection(boost::asio::io_context& io_context);

			// Handles the rest of the client connection
			void handle_write(const boost::system::error_code& error, size_t bytes_transferred);

			tcp::socket socket_;

			std::string message_;
	};
}
