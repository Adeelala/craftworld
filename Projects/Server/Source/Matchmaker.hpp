#pragma once

#include "Server.hpp"

namespace CraftWorld {
	/**
	 * Manages communication between Slaves and Clients.
	 */
	class Matchmaker : public Server {
		public:
			/**
			 * Creates a new Matchmaker.
			 * @param port The port to listen on.
			 */
			explicit Matchmaker(const int& port);
	};
}
