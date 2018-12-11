#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Entities {
	/**
	 * An entity represents a physical thing in the game world.
	 */
	class Entity {
			friend boost::serialization::access;

			/**
			 * Serializes the Entity.
			 * @tparam ArchiveType The type of archive used for serialization.
			 * @param archive The archive used for serialization.
			 * @param version The version of the serialization algorithm.
			 */
			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_NVP(velocity);
			}

		public:
			/**
			 * The current rate of movement of the entity, measured in Blocks per tick.
			 */
			Utility::Vector3D<int> velocity;

			/**
			 * Creates a new Entity.
			 * @param velocity The default speed.
			 */
			Entity(Utility::Vector3D<int> velocity = { 0, 0, 0 });

			/**
			 * Declares the class as polymorphic.
			 */
			virtual ~Entity() {
			};
	};
}

