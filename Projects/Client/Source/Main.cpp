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
	stringStream << data;
	boost::archive::text_iarchive archive(stringStream);

	// Deserialize the World
	World world;
	archive >> world;

	std::cout << "Deserialized world!" << std::endl;
}

int main(int argc, char* argv[]) {
	std::cout << "Starting client..." << std::endl;

	// Create new Client
	Client client("localhost", 8000);

	// Run the Client
	client.run(dataHandler);

	return 0;
}
