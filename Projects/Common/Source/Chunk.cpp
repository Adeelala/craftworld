#include "Chunk.hpp"

namespace CraftWorld {
	std::string Chunk::getHash() const {
		// TODO: Implement this
		return "";
	}

	void Chunk::update() {
		// Update entities
		for(auto& entity : entities_) {
			// Update the entity
			entity.update();
		}
	}
}
