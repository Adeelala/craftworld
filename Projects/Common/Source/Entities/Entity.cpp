#include "Entity.hpp"

namespace CraftWorld::Entities {
	Entity::Entity(Utility::Vector3D<int> velocity) : velocity(velocity) {
	}

	template<typename ArchiveType>
	void Entity::serialize(ArchiveType& archive) {
		velocity.serialize(archive);
	}
}
