#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

#include "../Utility/Vector3D.hpp"

namespace CraftWorld::Entities {
	class Entity {
			friend boost::serialization::access;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_NVP(velocity);
			}
			
		public:
			Utility::Vector3D<int> velocity;

			Entity(Utility::Vector3D<int> velocity = { 0, 0, 0 });

			virtual ~Entity() {
			}
	};
}

