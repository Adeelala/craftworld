#pragma once

#include <string>

#include "Action.hpp"

namespace CraftWorld::Actions {
	class ConnectAction : public Action {
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
			 * Creates a new ConnectAction.
			 * @param source The source of the Action.
			 * @param username The username of the player that was found.
			 */
			ConnectAction(const std::string& source, const std::string& username);
	};
}
