#pragma once

#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Entities {
	class Entity {
		public:
			Utility::Vector3D<int> velocity;

			Entity(Utility::Vector3D<int> velocity = { 0, 0, 0 });

			virtual ~Entity() = default;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				velocity.serialize(archive, version);
			}
	};
}
