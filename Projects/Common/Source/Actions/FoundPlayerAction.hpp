#pragma once

#include <string>

#include "Action.hpp"

namespace CraftWorld::Actions {
	class FoundPlayerAction : public Action {
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
				archive & BOOST_SERIALIZATION_NVP(username);
			}

		public:
			/**
			 * The player's username.
			 */
			std::string username;

			/**
			 * Creates a new FoundPlayerAction.
			 */
			FoundPlayerAction() = default;

			/**
			 * Creates a new FoundPlayerAction.
			 * @param source The source of the Action.
			 * @param username The username of the player that was found.
			 */
			FoundPlayerAction(const int& source, const std::string& username);
	};
}
