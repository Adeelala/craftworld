#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <cstdlib>

#include "Server.hpp"

using namespace CraftWorld;

int main(int argc, char* argv[]) {
	if(argc < 8) {
		std::cout << "Incorrect number of arguments" << std::endl;
		std::cout << "Correct usage: CraftWorld-Server {matchmakerCount} {matchmakerBasePort} {worldChunkSizeX} {worldChunkSizeY} {worldChunkSizeZ} {chunkBlockSizeX} {chunkBlockSizeY} {chunkBlockSizeZ}" << std::endl;

		return 1;
	}

	// Get the amount of matchmakers to initialize
	int matchmakerCount = atoi(argv[1]);
	std::cout << "Matchmaker count: " << matchmakerCount << std::endl;
	if(matchmakerCount < 1) {
		std::cout << "At least 1 matchmaker is needed" << std::endl;

		return 1;
	}

	// Get the base port for the matchmaker servers
	unsigned int matchmakerBasePort = atoi(argv[2]);
	std::cout << "Matchmaker base port: " << matchmakerBasePort << std::endl;

	Utility::Vector3D<int> worldChunkSize { atoi(argv[3]), atoi(argv[4]), atoi(argv[5]) };
	std::cout << "World chunk size: " << static_cast<std::string>(worldChunkSize) << std::endl;

	Utility::Vector3D<int> chunkBlockSize { atoi(argv[6]), atoi(argv[7]), atoi(argv[8]) };
	std::cout << "Chunk block size: " << static_cast<std::string>(chunkBlockSize) << std::endl;

	std::cout << "Starting server..." << std::endl;

	// Initialize the MPI environment
	boost::mpi::environment environment(argc, argv);

	// Get MPI world
	boost::mpi::communicator world;

	try {
		// Set up server
		Server server(matchmakerCount, matchmakerBasePort + world.rank(), worldChunkSize, chunkBlockSize);

		// Run the server
		server.run();
	} catch(std::exception& e) {
		std::cerr << "Failed to start server: " << e.what() << std::endl;

		return 1;
	}

	return 0;
}
