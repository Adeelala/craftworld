#include <array>
#include <string>
#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

std::string receiveData(tcp::socket& socket) {
	// Receive data
	std::array<char, 128> buffer;
	boost::system::error_code errorCode;
	size_t length = socket.read_some(boost::asio::buffer(buffer), errorCode);

	// Check if data was received
	if(errorCode == boost::asio::error::eof) {
		// The connection was closed, so exit
		exit(0);
	} else if(errorCode) {
		// An error occurred
		throw boost::system::system_error(errorCode);
	}

	// Return data
	return std::string(buffer.data(), length);
}

int main(int argc, char* argv[]) {
	std::cout << "Starting client..." << std::endl;

	// Initialize Boost Asio context
	boost::asio::io_context ioContext;

	// Resolve server endpoint
	tcp::resolver::results_type endpoints = tcp::resolver(ioContext).resolve("localhost", "8000");

	// Create new socket
	tcp::socket socket(ioContext);

	// Establish a connection
	try
	{
		boost::asio::connect(socket, endpoints);
	}
	catch(std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	// Keep looping to receive data
	while(true) {
		std::string data = receiveData(socket);

		// If we're here, print the data
		std::cout << data << std::flush;
	}

	return 0;
}
