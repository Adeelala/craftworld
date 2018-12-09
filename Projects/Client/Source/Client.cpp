#include "Client.hpp"

#include <iterator>
#include <iostream>

namespace CraftWorld {
	Client::Client(const std::string& host, const int& port) : socket(
		[&]() {
			// Initialize IO context
			boost::asio::io_context ioContext;

			// Resolve server endpoint
			tcp::resolver::results_type endpoints = tcp::resolver(ioContext).resolve(host, std::to_string(port));

			// Create new socket
			tcp::socket socket(ioContext);

			// Establish a connection
			try {
				boost::asio::connect(socket, endpoints);
			} catch(std::exception& e) {
				std::cerr << e.what() << std::endl;

				exit(1);
			}

			return socket;
		}()
	) {
	}

	void Client::run(const std::function<void(const std::string&)>& dataHandler) {
		// Keep looping to receive data
		while(true) {
			// Receive data
			std::string data;
			boost::system::error_code errorCode;
			size_t length = boost::asio::read_until(socket, boost::asio::dynamic_buffer(data), "\n\n", errorCode);
			data = data.substr(0, length - 2);

			// Check if data was received
			if(errorCode == boost::asio::error::eof) {
				// The connection was closed, so exit
				exit(0);
			} else if(errorCode) {
				// An error occurred
				throw boost::system::system_error(errorCode);
			}

			// Handle data
			std::cout << "Received data: " << std::endl << data << std::endl;
			dataHandler(data);
		}
	}
}
