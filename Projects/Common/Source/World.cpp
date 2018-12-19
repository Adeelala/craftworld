#include "World.hpp"

#include <memory>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(CraftWorld::World, "World")
BOOST_CLASS_EXPORT_GUID(CraftWorld::ChunkGrid, "ChunkGrid")

namespace CraftWorld {
	World World::generate(const Utility::Vector3D<int>& worldChunkSize, const Utility::Vector3D<int>& chunkBlockSize) {
		World world(worldChunkSize, chunkBlockSize);

		// Create some chunks
		world.forEach(
			[&](auto& entity) {
				entity = std::make_shared<Chunk>(Chunk::generate(chunkBlockSize));
			}
		);

		std::static_pointer_cast<Chunk>(world.entities[0][0][0])->entities[0][0][0] = std::make_shared<Entities::Player>(Entities::Player({ 0, 0, 0 }, "Steve"));

		return world;
	}

	World::World(const Utility::Vector3D<int>& worldChunkSize, const Utility::Vector3D<int>& chunkBlockSize) : ChunkGrid(worldChunkSize) {
		// Create some chunks
		forEach(
			[&](auto& entity) {
				entity = std::make_shared<Chunk>(Chunk(chunkBlockSize));
			}
		);
	}

	void World::update() {
		// Update all chunks
		forEach(
			[](auto& entity) {
				std::static_pointer_cast<Chunk>(entity)->update();
			}
		);
	}
}
