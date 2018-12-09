#pragma once

#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include "Grid.hpp"
#include "Chunk.hpp"
#include "Utility/Vector3D.hpp"
#include "Entities/Block.hpp"
#include "Entities/Player.hpp"

namespace CraftWorld {
	using ChunkGrid = Grid<Chunk>;

	class World :
		public ChunkGrid {
			friend boost::serialization::access;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				// We need to explicitly register these types as they're stored as pointers to their base class
				archive.register_type(static_cast<Entities::Block*>(nullptr));
				archive.register_type(static_cast<Entities::Player*>(nullptr));

				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ChunkGrid);
			}

		public:
			World();

			World(const Utility::Vector3D<int>& worldChunkSize, const Utility::Vector3D<int>& chunkBlockSize);

			void update();

			Utility::Vector3D<int> getChunkSize();

			std::vector<std::vector<char>> createMap();
	};
}
