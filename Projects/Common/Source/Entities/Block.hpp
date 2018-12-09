#pragma once

#include <boost/serialization/base_object.hpp>

#include "Entity.hpp"

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
				archive & boost::serialization::base_object<Entity>(*this);
				archive & type;
			}
	};
}
