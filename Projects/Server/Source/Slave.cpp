#include "Slave.hpp"

#include <iostream>

namespace CraftWorld {
	Slave::Slave(const int& port) : Server(port) {
		std::cout << "Server with rank " << world_.rank() << " is a slave" << std::endl;
	}
}
