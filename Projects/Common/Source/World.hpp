#pragma once

#include <vector>
#include <boost/serialization/export.hpp>
#include <boost/serialization/nvp.hpp>

#include "Grid.hpp"
#include "Entities/Chunk.hpp"

namespace CraftWorld {
	class World :
		public Grid<Entities::Chunk> {
		public:
			World();

			World(const Utility::Vector3D<int>& worldChunkSize, const Utility::Vector3D<int>& chunkBlockSize);

			void update();

			Utility::Vector3D<int> getChunkSize();

			std::vector<std::vector<char>> createMap();

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Grid<Entities::Chunk>);
			}
	};
}

BOOST_CLASS_EXPORT_KEY(CraftWorld::World)