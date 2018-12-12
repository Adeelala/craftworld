#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include "Entity.hpp"

namespace CraftWorld::Entities {
	/**
	 * Represents a square block, which the Player can pick up and place somewhere else.
	 */
	class Block :
		public Entity {
			friend boost::serialization::access;

			/**
			 * Serializes the Block.
			 * @tparam ArchiveType The type of archive used for serialization.
			 * @param archive The archive used for serialization.
			 * @param version The version of the serialization algorithm.
			 */
			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Entity);
				archive & BOOST_SERIALIZATION_NVP(type);
			}

		public:
			/**
			 * The types of material that are available.
			 */
			enum Type {
				AIR,
				DIRT
			};

			/**
			 * The material type.
			 */
			Type type;

			/**
			 * Creates a new Block.
			 * @param type The material type.
			 */
			Block(const Type& type = AIR);
	};
}
