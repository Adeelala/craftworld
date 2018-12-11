#pragma once

#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

namespace CraftWorld::Utility {
	template<typename Type>
	class Vector3D {
			friend boost::serialization::access;

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_NVP(x);
				archive & BOOST_SERIALIZATION_NVP(y);
				archive & BOOST_SERIALIZATION_NVP(z);
			}
			
		public:
			Type x;

			Type y;

			Type z;

			Vector3D() : Vector3D(0, 0, 0) {
			}

			Vector3D(const Type& x, const Type& y, const Type& z) : x(x), y(y), z(z) {
			}

			Vector3D& operator +=(const Vector3D& right) {
				x += right.x;
				y += right.y;
				z += right.z;

				return *this;
			}

			Vector3D& operator -=(const Vector3D& right) {
				x -= right.x;
				y -= right.y;
				z -= right.z;

				return *this;
			}

			Vector3D& operator *=(const Type& right) {
				x *= right.x;
				y *= right.y;
				z *= right.z;

				return *this;
			}

			friend bool operator ==(const Vector3D& left, const Vector3D& right) {
				return left.x == right.x && left.y == right.y && left.z == right.z;
			}

			friend Vector3D operator +(const Vector3D& left, const Vector3D& right) {
				return Vector3D(left) += right;
			}

			friend Vector3D operator -(const Vector3D& left, const Vector3D& right) {
				return Vector3D(left) -= right;
			}

			friend Vector3D operator *(const Vector3D& left, const Type& right) {
				return Vector3D(left) *= right;
			}
	};
}
