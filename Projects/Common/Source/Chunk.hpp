#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include "Grid.hpp"
#include "Entities/Entity.hpp"
#include "Utility/Vector3D.hpp"

namespace CraftWorld {
	class Chunk :
		public Grid<Entities::Entity> {
			friend boost::serialization::access;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & boost::serialization::base_object<Grid<Entities::Entity>>(*this);
			}
			
		public:
			Chunk();

			Chunk(const Utility::Vector3D<int>& blockSize);

			void update();

			/**
			 * Checks if the Chunk contains only air blocks.
			 * @return Whether the Chunk is empty.
			 */
			bool isEmpty() const;
	};
}
