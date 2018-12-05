#pragma once

#include <string>
#include <vector>

#include "Grid.hpp"
#include "Entity.hpp"

namespace CraftWorld {
	class Chunk :
		public Grid<Entity, int> {
		public:
			void update();

			std::string getHash() const;
	};
}
