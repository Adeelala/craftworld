#include "World.hpp"

#include <memory>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::World, "World")
BOOST_CLASS_EXPORT_GUID(CraftWorld::ChunkGrid, "ChunkGrid")

namespace CraftWorld {
	World::World(const Utility::Vector3D<int>& worldChunkSize, const Utility::Vector3D<int>& chunkBlockSize) : ChunkGrid(worldChunkSize) {
		// Create some chunks
		for(int x = 0; x < entities.size(); ++x) {
			for(int y = 0; y < entities[x].size(); ++y) {
				for(int z = 0; z < entities[x][y].size(); ++z) {
					entities[x][y][z] = std::make_shared<Chunk>(Chunk(chunkBlockSize));
				}
			}
		}
	}

	void World::update() {
		// Update all chunks
		for(int x = 0; x < entities.size(); ++x) {
			for(int y = 0; y < entities[x].size(); ++y) {
				for(int z = 0; z < entities[x][y].size(); ++z) {
					std::static_pointer_cast<Chunk>(entities[x][y][z])->update();
				}
			}
		}
	}
}
