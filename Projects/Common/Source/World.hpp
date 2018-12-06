#pragma once

#include <vector>

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
	};
}