#pragma once

#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Entities {
	class Entity {
		public:
			Utility::Vector3D<int> velocity;

			Entity(Utility::Vector3D<int> velocity);

			virtual ~Entity() = default;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive);
	};
}
