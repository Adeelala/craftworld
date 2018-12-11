#pragma once

#include <memory>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include "Entity.hpp"
#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Entities {
	class Player :
		public Entity {
			friend boost::serialization::access;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Entity);
			}
			
		public:
			Player(const Utility::Vector3D<int>& velocity = { 0, 0, 0 });
	};
}
