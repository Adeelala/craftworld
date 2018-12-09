#pragma once

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

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & entities;
			}
			
		public:
			std::vector<std::vector<std::vector<std::shared_ptr<Type>>>> entities;

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
	};
}

