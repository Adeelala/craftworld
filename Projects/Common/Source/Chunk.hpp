#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include "Grid.hpp"
#include "Entities/Entity.hpp"
#include "Utility/Vector3D.hpp"
#include "Entities/Block.hpp"
#include "Entities/Player.hpp"

namespace CraftWorld {
	using EntityGrid = Grid<Entities::Entity>;

	/**
	 * An area of the World that contains Entities on a 3D grid.
	 */
	class Chunk :
		public EntityGrid {
			friend boost::serialization::access;

			/**
			 * Serializes the Chunk.
			 * @tparam ArchiveType The type of archive used for serialization.
			 * @param archive The archive used for serialization.
			 * @param version The version of the serialization algorithm.
			 */
			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				// We need to explicitly register these types as they're stored as pointers to their base class
				archive.register_type(static_cast<Entities::Block*>(nullptr));
				archive.register_type(static_cast<Entities::Player*>(nullptr));

				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(EntityGrid);
			}

		public:
			/**
			 * Generates a new Chunk.
			 * @param blockSize The amount of Blocks the Chunk should be able to contain, in every dimension.
			 * @return The new Chunk.
			 */
			static Chunk generate(const Utility::Vector3D<int>& blockSize);

			/**
			 * Creates a new Chunk.
			 */
			Chunk() = default;

			/**
			 * Creates a new Chunk.
			 * @param blockSize The amount of Blocks the Chunk should be able to contain, in every dimension.
			 */
			Chunk(const Utility::Vector3D<int>& blockSize);

			/**
			 * Performs a tick for all Entitites in the Chunk.
			 */
			void update();

			/**
			 * Checks if the Chunk contains only air blocks.
			 * @return Whether the Chunk is empty.
			 */
			bool isEmpty() const;
	};
}
