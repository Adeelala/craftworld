#pragma once

#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include "Grid.hpp"
#include "Chunk.hpp"
#include "Utility/Vector3D.hpp"

namespace CraftWorld {
	using ChunkGrid = Grid<Chunk>;

	class World :
		public ChunkGrid {
			friend boost::serialization::access;

			/**
			 * Serializes the World.
			 * @tparam ArchiveType The type of archive used for serialization.
			 * @param archive The archive used for serialization.
			 * @param version The version of the serialization algorithm.
			 */
			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ChunkGrid);
			}

		public:
			/**
			 * Generates a new World.
			 * @param worldChunkSize The amount of Chunks the World should contain on each axis.
			 * @param chunkBlockSize The amount of Blocks every Chunk should contain on each axis.
			 * @return The new World.
			 */
			static World generate(const Utility::Vector3D<int>& worldChunkSize, const Utility::Vector3D<int>& chunkBlockSize);

			/**
			 * Creates a new World.
			 */
			World() = default;

			/**
			 * Creates a new World.
			 * @param worldChunkSize The amount of Chunks the World should contain on each axis.
			 * @param chunkBlockSize The amount of Blocks every Chunk should contain on each axis.
			 */
			World(const Utility::Vector3D<int>& worldChunkSize, const Utility::Vector3D<int>& chunkBlockSize);

			/**
			 * Performs a tick for all Chunks in the World.
			 */
			void update();
	};
}
