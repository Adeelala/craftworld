#include <iostream>
#include <boost/asio.hpp>
#include <boost/mpi/environment.hpp>

#include "Server.hpp"

using namespace CraftWorld;

int main(int argc, char* argv[]) {
	std::cout << "Starting server..." << std::endl;

	// Initialize the MPI environment
	boost::mpi::environment environment(argc, argv);

	try {
		// Create the server object that is going to accept connections
		Server server(8000);

		// Run the IO context so that it will perform asynchronous operations
		server.run();
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
