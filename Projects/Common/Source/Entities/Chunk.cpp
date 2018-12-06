#include "Chunk.hpp"

#include <memory>

#include "Block.hpp"

namespace CraftWorld::Entities {
	Chunk::Chunk() : Entity(Utility::Vector3D<int> { 0, 0, 0 }) {
	}

	Chunk::Chunk(const Utility::Vector3D<int>& blockSize) : Entity(Utility::Vector3D<int> { 0, 0, 0 }), Grid(blockSize) {
		// Fill the chunk with blocks
		for(int x = 0; x < blockSize.x; ++x) {
			for(int y = 0; y < blockSize.y; ++y) {
				for(int z = 0; z < blockSize.z; ++z) {
					entities[x][y][z] =
						std::make_shared<Block>(
							Block(
								y < (blockSize.y / 2)
									? Block::DIRT
									: Block::AIR
							)
						);
				}
			}
		}
	}

	void Chunk::update() {
		// Update entities
		for(int x = 0; x < entities.size(); ++x) {
			for(int y = 0; y < entities[x].size(); ++y) {
				for(int z = 0; z < entities[x][y].size(); ++z) {
					auto entity = entities[x][y][z];

					// Update position
					Utility::Vector3D<int> position { x, y, z };
					Utility::Vector3D<int> newPosition = position + entity->velocity;
					swap(position, newPosition);
				}
			}
		}
	}

	bool Chunk::isEmpty() const {
		for(int x = 0; x < entities.size(); ++x) {
			for(int y = 0; y < entities[x].size(); ++y) {
				for(int z = 0; z < entities[x][y].size(); ++z) {
					// Check if the entity is a block and if the block is air
					if(
						auto pointer = dynamic_cast<Block*>(entities[x][y][z].get());
						pointer != nullptr && pointer->type != Block::AIR
						) {
						return false;
					}
				}
			}
		}

		return true;
	}
}
