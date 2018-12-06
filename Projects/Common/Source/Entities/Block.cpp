#include "Block.hpp"

namespace CraftWorld::Entities {
	Block::Block(const Block::Type& type) : Entity(Utility::Vector3D<int> { 0, 0, 0 }), type(type) {
	}
}

