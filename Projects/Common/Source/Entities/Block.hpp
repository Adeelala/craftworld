#pragma once

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>

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
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Entity);
				archive & type;
			}
	};
}

BOOST_CLASS_EXPORT_KEY(CraftWorld::Entities::Block)
