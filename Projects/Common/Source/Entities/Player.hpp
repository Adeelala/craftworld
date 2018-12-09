#pragma once

#include <memory>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include "Entity.hpp"
#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Entities {
	class Player :
		public Entity {
			friend boost::serialization::access;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & boost::serialization::base_object<Entity>(*this);
			}
			
		public:
			Player(const Utility::Vector3D<int>& velocity = { 0, 0, 0 });
	};
}
