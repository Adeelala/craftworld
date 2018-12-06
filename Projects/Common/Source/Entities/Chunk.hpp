#pragma once

#include <string>
#include <vector>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>

#include "Entity.hpp"
#include "../Grid.hpp"
#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Entities {
	class Chunk :
		public Entity,
		public Grid<Entities::Entity> {
		public:
			Chunk();

			Chunk(const Utility::Vector3D<int>& blockSize);

			void update();

			/**
			 * Checks if the Chunk contains only air blocks.
			 * @return Whether the Chunk is empty.
			 */
			bool isEmpty() const;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Entity);
				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Grid<Entities::Entity>);
			}
	};
}

BOOST_CLASS_EXPORT_KEY(CraftWorld::Entities::Chunk)
