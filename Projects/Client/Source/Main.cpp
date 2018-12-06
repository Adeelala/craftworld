#include <array>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/archive/text_iarchive.hpp>

#include "Client.hpp"
#include "World.hpp"

using namespace CraftWorld;

void dataHandler(const std::string& data) {
	// Create serialization stream
	std::stringstream stringStream;
	boost::archive::text_iarchive archive(stringStream);

	// Write input data to the stream
	stringStream << data;

	// Deserialize the World
	World world;
	world.serialize(archive, 1);

	std::cout << "Deserialized world!";
}

int main(int argc, char* argv[]) {
	std::cout << "Starting client..." << std::endl;

	// Create new Client
	Client client("localhost", 8000);

	// Run the Client
	client.run(dataHandler);

	return 0;
}
