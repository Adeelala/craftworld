#pragma once

#include <vector>

#include "Grid.hpp"
#include "Chunk.hpp"

namespace CraftWorld {
	class World :
		public Grid<Chunk, int> {
		public:
			void update();
	};
}