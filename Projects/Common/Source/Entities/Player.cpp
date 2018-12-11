#include "Player.hpp"

#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::Entities::Player, "Player")

namespace CraftWorld::Entities {
	Player::Player(const Utility::Vector3D<int>& velocity) : Entity(velocity) {
	}
}
