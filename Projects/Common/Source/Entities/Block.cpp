#include "Block.hpp"

#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/export.hpp>

#include "../Utility/Vector3D.hpp"

BOOST_CLASS_EXPORT_GUID(CraftWorld::Entities::Block, "Block")

namespace CraftWorld::Entities {
	Block::Block(const Block::Type& type) : Entity(Utility::Vector3D<int> { 0, 0, 0 }), type(type) {
	}
}
