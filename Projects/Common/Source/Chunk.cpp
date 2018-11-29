#include "Chunk.hpp"

namespace CraftWorld {
	std::string Chunk::getHash() const {
		// TODO: Implement this
		return "";
	}

	void Chunk::update() {
		// Update entities
		for(auto& entity : entities) {
			// Add gravity
			entity.speedUp(Vector3D(0, -1, 0));

			// Update the entity
			entity.update();
		}
	}
}
