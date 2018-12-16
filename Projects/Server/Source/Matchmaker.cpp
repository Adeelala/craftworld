#include "Matchmaker.hpp"

#include <iostream>

namespace CraftWorld {
	Matchmaker::Matchmaker(const int& port) : Server(port) {
		std::cout << "Server with rank " << world_.rank() << " is the matchmaker" << std::endl;
	}
}
