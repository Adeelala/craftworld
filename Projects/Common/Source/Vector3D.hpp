#pragma once

#include <vector>

namespace CraftWorld {
	template<typename Type>
	class Vector3D {
			std::vector<Type> value;

		public:
			Vector3D() : Vector3D(0, 0, 0) {
			}

			Vector3D(const Type& x, const Type& y, const Type& z) : value(
				{
					x,
					y,
					z
				}
			) {
			}

			Vector3D& operator +=(const Vector3D& right) {
				value[0] += right.value[0];
				value[1] += right.value[1];
				value[2] += right.value[2];

				return *this;
			}

			Vector3D& operator -=(const Vector3D& right) {
				value[0] -= right.value[0];
				value[1] -= right.value[1];
				value[2] -= right.value[2];

				return *this;
			}

			Vector3D& operator *=(const Type& right) {
				value[0] *= right;
				value[1] *= right;
				value[2] *= right;

				return *this;
			}

			friend bool operator ==(const Vector3D& left, const Vector3D& right) {
				return left.value == right.value;
			}

			friend bool operator <(const Vector3D& left, const Vector3D& right) {
				return left.value < right.value;
			}

			friend bool operator >(const Vector3D& left, const Vector3D& right) {
				return left.value > right.value;
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
