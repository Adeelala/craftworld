#include "World.hpp"

#include <memory>

#include "Entities/Chunk.hpp"

namespace CraftWorld {
	World::World() {
	}

	World::World(const Utility::Vector3D<int>& worldChunkSize, const Utility::Vector3D<int>& chunkBlockSize) : Grid(worldChunkSize) {
		// Create some chunks
		for(int x = 0; x < entities.size(); ++x) {
			for(int y = 0; y < entities[x].size(); ++y) {
				for(int z = 0; z < entities[x][y].size(); ++z) {
					entities[x][y][z] = std::make_shared<Entities::Chunk>(Entities::Chunk(chunkBlockSize));
				}
			}
		}
	}

	void World::update() {
		// Update all chunks
		for(int x = 0; x < entities.size(); ++x) {
			for(int y = 0; y < entities[x].size(); ++y) {
				for(int z = 0; z < entities[x][y].size(); ++z) {
					std::static_pointer_cast<Entities::Chunk>(entities[x][y][z])->update();
				}
			}
		}
	}

	std::vector<std::vector<char>> World::createMap() {
		// Detect map size
		Utility::Vector3D<int> size = { entities.size(), 0, 0 };
		for(int x = 0; x < entities.size(); ++x) {
			if(entities[x].size() > size.y) {
				size.y = entities[x].size();
			}
			for(int y = 0; y < entities[x].size(); ++y) {
				if(entities[x][y].size() > size.z) {
					size.z = entities[x][y].size();
				}
			}
		}

		// Create vector to hold result
		std::vector<std::vector<char>> result(size.x, std::vector<char>(size.z, 'A'));

		// TODO: Write actual map code

		return result;
	}
}
