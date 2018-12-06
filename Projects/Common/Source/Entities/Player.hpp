#pragma once

#include <memory>

#include "Block.hpp"
#include "Entity.hpp"
#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Entities {
	class Player :
		public Entity {
		public:
			Player(const Utility::Vector3D<int>& velocity = { 0, 0, 0 });
	};
}
