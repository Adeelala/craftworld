#include "Player.hpp"

namespace CraftWorld::Entities {
	Player::Player(const Utility::Vector3D<int>& velocity) : Entity(velocity) {
	}
}

BOOST_CLASS_EXPORT_IMPLEMENT(CraftWorld::Entities::Player)
