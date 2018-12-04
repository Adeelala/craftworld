#pragma once

#include <string>
#include <vector>

#include "Grid.hpp"
#include "Entity.hpp"

namespace CraftWorld {
	class Chunk {
			Grid<Entity, int> entities_;

		public:
			void update();

			std::string getHash() const;
	};
}
