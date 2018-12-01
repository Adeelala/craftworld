#include <array>
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

int main(int argc, char* argv[]) {
	std::cout << "Starting client...";

	// Initialize Boost Asio context
	boost::asio::io_context ioContext;

	// Resolve server endpoint
	tcp::resolver::results_type endpoints = tcp::resolver(ioContext).resolve("localhost", "8000");

	// Create new socket
	tcp::socket socket(ioContext);

	// Establish a connection
	boost::asio::connect(socket, endpoints);

	// Keep looping to receive data
	while(true) {
		// Receive data
		std::array<char, 128> buffer;
		boost::system::error_code errorCode;
		size_t length = socket.read_some(boost::asio::buffer(buffer), errorCode);

		// Check if data was received
		if(errorCode == boost::asio::error::eof) {
			// The connection was closed, so exit
			break;
		} else if(errorCode) {
			// An error occurred
			throw boost::system::system_error(errorCode);
		}

		// If we're here, print the data
		std::cout.write(buffer.data(), length);
	}

	return 0;
}
