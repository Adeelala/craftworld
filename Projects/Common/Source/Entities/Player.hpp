#pragma once

#include <memory>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>

#include "Block.hpp"
#include "Entity.hpp"
#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Entities {
	class Player :
		public Entity {
		public:
			Player(const Utility::Vector3D<int>& velocity = { 0, 0, 0 });

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & boost::serialization::base_object<Entity>(*this);
			}
	};
}

BOOST_CLASS_EXPORT_KEY(CraftWorld::Entities::Player)
