#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include "Grid.hpp"
#include "Entities/Entity.hpp"
#include "Utility/Vector3D.hpp"

namespace CraftWorld {
	using EntityGrid = Grid<Entities::Entity>;

	class Chunk :
		public EntityGrid {
			friend boost::serialization::access;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(EntityGrid);
			}

		public:
			Chunk() = default;

			Chunk(const Utility::Vector3D<int>& blockSize);

			void update();

			/**
			 * Checks if the Chunk contains only air blocks.
			 * @return Whether the Chunk is empty.
			 */
			bool isEmpty() const;
	};
}
