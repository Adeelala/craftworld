#include <iostream>
#include <boost/asio.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>

#include "Matchmaker.hpp"
#include "Slave.hpp"

using namespace CraftWorld;

int main(int argc, char* argv[]) {
	std::cout << "Starting server..." << std::endl;

	// Initialize the MPI environment
	boost::mpi::environment environment(argc, argv);

	// Get MPI world
	boost::mpi::communicator world;

	try {
		// Set up servers
		if(world.rank() == 0) {
			// Set up the matchmaker
			Matchmaker server(8000);

			// Run the matchmaker
			server.run();
		} else {
			// Set up a new slave
			Slave server(8000);

			// Run the slave
			server.run();
		}
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
