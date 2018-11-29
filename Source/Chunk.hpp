#pragma once

#include <vector>

#include "Block.hpp"

namespace Craftworld {
	class Chunk {
			std::vector<std::vector<std::vector<Block>>> blocks;
	};
}
