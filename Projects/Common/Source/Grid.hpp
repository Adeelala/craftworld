#pragma once

#include <memory>
#include <vector>

#include "Entities/Entity.hpp"
#include "Utility/Vector3D.hpp"

namespace CraftWorld {
	template<typename Type>
	class Grid {
		public:
			std::vector<std::vector<std::vector<std::shared_ptr<Type>>>> entities;

			Grid() {
			}

			Grid(const Utility::Vector3D<int>& size) : entities(
				std::vector<std::vector<std::vector<std::shared_ptr<Type>>>>(
					size.x,
					std::vector<std::vector<std::shared_ptr<Type>>>(
						size.y,
						std::vector<std::shared_ptr<Type>>(
							size.z,
							std::shared_ptr<Type>()
						)
					)
				)
			) {
			}

			/**
			 * Swaps the entities at the two positions
			 * @param first The first position.
			 * @param second The second position.
			 */
			void swap(const Utility::Vector3D<int>& first, const Utility::Vector3D<int>& second) {
				std::shared_ptr<Entities::Entity> temporary = entities[second.x][second.y][second.z];
				entities[second.x][second.y][second.z] = entities[first.x][first.y][first.z];
				entities[first.x][first.y][first.z] = temporary;
			}

			template<typename ArchiveType>
			void serialize(ArchiveType& archive) {
				archive & entities;
			}
	};
}
