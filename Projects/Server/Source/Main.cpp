#include <iostream>
#include <boost/asio.hpp>

#include "Server.hpp"
#include "World.hpp"

int main(int argc, char* argv[]) {
	using namespace CraftWorld::Server;

	std::cout << "Starting server..." << std::endl;

	try {
		// Create the server object that is going to accept connections
		boost::asio::io_context io_context;
		Server server(io_context);

		// Run the IO context so that it will perform asynchronous operations
		io_context.run();
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
