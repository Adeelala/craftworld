#pragma once

#include "Entity.hpp"
#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Entities {
	class Block :
		public Entity {
		public:
			enum Type {
				AIR,
				DIRT
			};

			Type type;

			Block(const Type& type = AIR);

			template<typename ArchiveType>
			void serialize(ArchiveType& archive);
	};
}
