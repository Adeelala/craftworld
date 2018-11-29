#pragma once

#include <vector>

#include "Chunk.hpp"

namespace Craftworld {
	class World {
			std::vector<std::vector<std::vector<Chunk>>> chunks;
	};
}