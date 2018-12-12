#include "Entity.hpp"

#include <boost/serialization/export.hpp>
#include <boost/serialization/assume_abstract.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::Entities::Entity, "Entity")
BOOST_SERIALIZATION_ASSUME_ABSTRACT(CraftWorld::Entities::Entity);

namespace CraftWorld::Entities {
	Entity::Entity(Utility::Vector3D<int> velocity) : velocity(velocity) {
	}
}
