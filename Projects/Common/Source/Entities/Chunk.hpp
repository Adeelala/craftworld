#pragma once

#include <string>
#include <vector>

#include "Entity.hpp"
#include "../Grid.hpp"
#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Entities {
	class Chunk :
		public Entity,
		public Grid<Entities::Entity> {
		public:
			Chunk();

			Chunk(const Utility::Vector3D<int>& blockSize);

			void update();

			/**
			 * Checks if the Chunk contains only air blocks.
			 * @return Whether the Chunk is empty.
			 */
			bool isEmpty() const;
	};
}
