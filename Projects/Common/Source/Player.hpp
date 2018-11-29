#pragma once

#include <vector>

#include "Entity.hpp"

namespace Craftworld {
	class Player :
		public Entity {
			std::vector<Entity> inventory;
	};
}
