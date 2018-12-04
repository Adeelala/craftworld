#include "World.hpp"

namespace CraftWorld {
	void World::update() {
		// Update all chunks
		for(auto& chunk : chunks_) {
			chunk.update();
		}
	}
}