#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

#include "Utility/Vector3D.hpp"

namespace CraftWorld {
	template<typename Type>
	class Grid {
			friend boost::serialization::access;

			/**
			 * Serializes the Chunk.
			 * @tparam ArchiveType The type of archive used for serialization.
			 * @param archive The archive used for serialization.
			 * @param version The version of the serialization algorithm.
			 */
			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_NVP(entities);
			}

		public:
			/**
			 * The entities contained within the Grid.
			 */
			std::vector<std::vector<std::vector<std::shared_ptr<Type>>>> entities;

			/**
			 * Creates a new Grid.
			 * @param size The amount of entities the Grid should be able to contain on each axis.
			 */
			Grid(const Utility::Vector3D<int>& size = { 0, 0, 0 }) : entities(
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
			 * Swaps the entities at the two positions.
			 * @param first The first position.
			 * @param second The second position.
			 */
			void swap(const Utility::Vector3D<int>& first, const Utility::Vector3D<int>& second) {
				std::shared_ptr<Type> temporary = entities[second.x][second.y][second.z];
				entities[second.x][second.y][second.z] = entities[first.x][first.y][first.z];
				entities[first.x][first.y][first.z] = temporary;
			}

			/**
			 * Gets the amount of entities in the Grid.
			 * @return The amount of entities.
			 */
			Utility::Vector3D<int> getSize() const {
				Utility::Vector3D<int> result;

				result.x = static_cast<int>(entities.size());

				for(const auto& yAxis : entities) {
					if(yAxis.size() > result.y) {
						result.y = static_cast<int>(yAxis.size());
					}

					for(const auto& zAxis : yAxis) {
						if(zAxis.size() > result.z) {
							result.z = static_cast<int>(zAxis.size());
						}
					}
				}

				return result;
			}

			/**
			 * Loops all entities in the grid.
			 * @param function The function to perform for all entities.
			 */
			void forEach(const std::function<void(std::shared_ptr<Type>&)>& function) {
				for(auto& yAxis : entities) {
					for(auto& zAxis : yAxis) {
						for(auto& entity : zAxis) {
							function(entity);
						}
					}
				}
			}
	};
}

