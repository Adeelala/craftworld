#pragma once

#include <vector>

#include "Entity.hpp"

namespace CraftWorld {
	class Player :
		public Entity {
			std::vector<Entity> inventory;

		public:
			void putInInventory(const Entity& entity);

			Entity removeFromInventory(const int& itemIndex);

			void clearInventory();
	};
}
