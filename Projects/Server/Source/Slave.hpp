#pragma once

#include "Server.hpp"

namespace CraftWorld {
	/**
	 * Contains and manages a part of the world.
	 */
	class Slave : public Server {
		public:
			/**
			 * Creates a new Slave.
			 * @param port The port to listen on.
			 */
			explicit Slave(const int& port);
	};
}
