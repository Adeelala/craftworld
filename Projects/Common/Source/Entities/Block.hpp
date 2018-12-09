#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include "Entity.hpp"

namespace CraftWorld::Entities {
	class Block :
		public Entity {
			friend boost::serialization::access;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & boost::serialization::base_object<Entity>(*this);
				archive & type;
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
