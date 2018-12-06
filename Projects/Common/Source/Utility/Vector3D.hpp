#pragma once

#include <vector>

namespace CraftWorld::Utility {
	template<typename Type>
	class Vector3D {
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

			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & x;
				archive & y;
				archive & z;
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
