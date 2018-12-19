#pragma once

#include <string>

#include "Action.hpp"

namespace CraftWorld::Actions {
	class PickUpBlockAction :
		public Action {
			friend boost::serialization::access;

			/**
			 * Serializes the Action.
			 * @tparam ArchiveType The type of archive used for serialization.
			 * @param archive The archive used for serialization.
			 * @param version The version of the serialization algorithm.
			 */
			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Action);
				archive & BOOST_SERIALIZATION_NVP(direction);
			}

		public:
			enum Direction {
				NORTH,
				EAST,
				SOUTH,
				WEST
			};

			/**
			 * The player's username.
			 */
			 Direction direction;

			/**
			 * Creates a new PickUpBlockAction.
			 */
			PickUpBlockAction() = default;

			/**
			 * Creates a new PickUpBlockAction.
			 * @param source The source of the Action.
			 * @param direction The username of the player to locate.
			 */
			PickUpBlockAction(const int& source, const Direction& direction);
	};
}
