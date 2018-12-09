#include "Entity.hpp"

#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::Entities::Entity, "Entity")

namespace CraftWorld::Entities {
	Entity::Entity(Utility::Vector3D<int> velocity) : velocity(velocity) {
	}
}
