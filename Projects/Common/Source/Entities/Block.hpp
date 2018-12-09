#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include "Entity.hpp"

namespace CraftWorld::Entities {
	class Block :
		public Entity {
			friend boost::serialization::access;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Entity);
				archive & BOOST_SERIALIZATION_NVP(type);
			}
			
		public:
			enum Type {
				AIR,
				DIRT
			};

			Type type;

			Block(const Type& type = AIR);
	};
}
