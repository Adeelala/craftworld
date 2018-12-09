#pragma once

#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include "Grid.hpp"
#include "Chunk.hpp"
#include "Utility/Vector3D.hpp"

namespace CraftWorld {
	class World :
		public Grid<Chunk> {
			friend boost::serialization::access;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & boost::serialization::base_object<Grid<Chunk>>(*this);
			}

		public:
			World();

			World(const Utility::Vector3D<int>& worldChunkSize, const Utility::Vector3D<int>& chunkBlockSize);

			void update();

			Utility::Vector3D<int> getChunkSize();

			std::vector<std::vector<char>> createMap();
	};
}
