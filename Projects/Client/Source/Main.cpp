#include <array>
#include <string>
#include <sstream>
#include <iostream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/nvp.hpp>

#include "Client.hpp"

using namespace CraftWorld;

int main(int argc, char* argv[]) {
	std::cout << "Starting client..." << std::endl;

	// Create new Client
	Client client("localhost", 8000);

	// Run the Client
	client.run();

	return 0;
}
