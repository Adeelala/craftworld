#include <iostream>
#include <boost/asio.hpp>

#include "Server.hpp"

using namespace CraftWorld;

int main(int argc, char* argv[]) {
	std::cout << "Starting server..." << std::endl;

	try {
		// Create the server object that is going to accept connections
		Server server;

		// Run the IO context so that it will perform asynchronous operations
		server.run();
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
