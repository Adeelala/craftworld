#pragma once

#include <vector>

#include "Grid.hpp"
#include "Chunk.hpp"

namespace CraftWorld {
	class World {
			Grid<Chunk, int> chunks_;

		public:
			void update();
	};
}