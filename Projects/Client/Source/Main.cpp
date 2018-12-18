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
 * Handles incoming data.
 * @param data The data.
 */
void dataHandler(const std::string& data) {
	// Create serialization stream
	std::stringstream stringStream;
	stringStream << data;
	boost::archive::text_iarchive archive(stringStream);

	// Deserialize the World
	World world;
	archive >> BOOST_SERIALIZATION_NVP(world);

	// TODO: overwrite the current world in client to this new one
	std::cout << "Deserialized world!" << std::endl;
}

int main(int argc, char* argv[]) {
	std::cout << "Starting client..." << std::endl;
      
        // I am doing it this way as portability to World is not working properly.
        // First phase: Map generation
        // Steps:
        // 1. Select map
        // 2. Partition into 10x10 areas
        // 3. For each area, pick center coordinate: this is the waypoint of the area.
        // 4. Add weights to each area, connect points
	// Create N new Clients
        
        int N = 100;
        for(int i = 0; i < N; i++) {
        	Client client("localhost", 8000);
        	client.run(dataHandler);    
        }
	return 0;
}
