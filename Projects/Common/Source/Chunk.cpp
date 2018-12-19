#include "Chunk.hpp"

#include <memory>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

#include "Entities/Block.hpp"
#include "Entities/Player.hpp"

BOOST_CLASS_EXPORT_GUID(CraftWorld::Chunk, "Chunk")
BOOST_CLASS_EXPORT_GUID(CraftWorld::EntityGrid, "EntityGrid")

namespace CraftWorld {
	Chunk Chunk::generate(const Utility::Vector3D<int>& blockSize) {
		Chunk chunk(blockSize);

		// Fill the chunk with blocks
		for(int x = 0; x < blockSize.x; ++x) {
			for(int y = 0; y < blockSize.y; ++y) {
				for(int z = 0; z < blockSize.z; ++z) {
					chunk.entities[x][y][z] = std::make_shared<Entities::Block>(
						y < (blockSize.y / 2)
							? Entities::Block::DIRT
							: Entities::Block::AIR
					);
				}
			}
		}

		return chunk;
	}

	Chunk::Chunk(const Utility::Vector3D<int>& blockSize) : EntityGrid(blockSize) {
		// Fill the chunk with blocks
		forEach(
			[](auto& entity) {
				entity = std::make_shared<Entities::Block>(Entities::Block::AIR);
			}
		);
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
						auto pointer = dynamic_cast<Entities::Block*>(entities[x][y][z].get());
						pointer != nullptr && pointer->type != Entities::Block::AIR
						) {
						return false;
					}
				}
			}
		}

		return true;
	}
}
