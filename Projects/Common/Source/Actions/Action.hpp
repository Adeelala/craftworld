#pragma once

#include <string>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/export.hpp>

#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Actions {
	/**
	 * Represents changes in the game state.
	 */
	class Action {
			friend boost::serialization::access;

			/**
			 * Serializes the Action.
			 * @tparam ArchiveType The type of archive used for serialization.
			 * @param archive The archive used for serialization.
			 * @param version The version of the serialization algorithm.
			 */
			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_NVP(name);
			}

		public:
			/**
			 * The name of the action.
			 */
			std::string name;

			/**
			 * The source of the action.
			 */
			std::string source;

			/**
			 * Creates a new Action.
			 */
			Action() = default;

			/**
			 * Creates a new Action.
			 * @param name The name.
			 * @param source The source.
			 */
			Action(const std::string& name, const std::string& source = "");

			/**
			 * Declares the class as polymorphic.
			 */
			virtual ~Action() = default;
	};
}

