#pragma once

#include <string>
#include <vector>

#include "Entity.hpp"

namespace CraftWorld {
	class Chunk {
			std::vector<Entity> entities;

		public:
			void update();

			std::string getHash() const;
	};
}
