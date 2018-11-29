#pragma once

#include <vector>

#include "Chunk.hpp"

namespace CraftWorld {
	class World {
			std::vector<Chunk> chunks;

		public:
			void update();
	};
}