#pragma once

#include <string>

#include "Action.hpp"
#include "../World.hpp"

namespace CraftWorld::Actions {
	class GetWorldAction :
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
			}

		public:
			/**
			 * Creates a new GetWorldAction.
			 */
			GetWorldAction() = default;

			/**
			 * Creates a new GetWorldAction.
			 * @param source The source of the Action.
			 * @param world The world to update.
			 */
			GetWorldAction(const int& source);
	};
}
