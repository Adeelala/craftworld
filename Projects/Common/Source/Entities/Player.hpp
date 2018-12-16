#pragma once

#include <memory>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include "Entity.hpp"
#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Entities {
	/**
	 * Represents a user of the game.
	 */
	class Player :
		public Entity {
			friend boost::serialization::access;

			/**
			 * Serializes the Player.
			 * @tparam ArchiveType The type of archive used for serialization.
			 * @param archive The archive used for serialization.
			 * @param version The version of the serialization algorithm.
			 */
			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Entity);
			}

		public:
			/**
			 * Creates a new Player.
			 * @param velocity The default speed.
			 */
			Player(const Utility::Vector3D<int>& velocity = { 0, 0, 0 });
	};
}
