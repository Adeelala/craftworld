#include <array>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/nvp.hpp>

#include "Client.hpp"
#include "World.hpp"

using namespace CraftWorld;

/**
 * Handles incomming data.
 * @param data The data.
 */
void dataHandler(const std::string& data) {
	//// Create serialization stream
	//std::stringstream stringStream;
	//stringStream << data;
	//boost::archive::text_iarchive archive(stringStream);
	//
	//// Deserialize the World
	//World world;
	//archive >> BOOST_SERIALIZATION_NVP(world);
	//
	//// TODO: overwrite the current world in client to this new one
	//std::cout << "Deserialized world!" << std::endl;
}

int main(int argc, char* argv[]) {
	std::cout << "Starting client..." << std::endl;

	// Create new Client
	Client client("localhost", 8000);

	// Run the Client
	client.run(dataHandler);

	return 0;
}
