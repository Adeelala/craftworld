#pragma once

#include <string>
#include <vector>

#include "Entity.hpp"

namespace Craftworld {
	class Chunk {
			std::vector<std::vector<std::vector<Entity>>> entities;

		public:
			std::string getHash() const;
	};
}
