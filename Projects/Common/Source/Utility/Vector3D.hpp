#pragma once

#include <string>
#include <vector>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

namespace CraftWorld::Utility {
	/**
	 * Used to represent a point on three axes.
	 * @tparam Type The numeric type used to represent an axis.
	 */
	template<typename Type>
	class Vector3D {
			friend boost::serialization::access;

			/**
			 * Serializes the Vector3D.
			 * @tparam ArchiveType The type of archive used for serialization.
			 * @param archive The archive used for serialization.
			 * @param version The version of the serialization algorithm.
			 */
			template<typename ArchiveType>
			void serialize(ArchiveType& archive, const unsigned int& version) {
				archive & BOOST_SERIALIZATION_NVP(x);
				archive & BOOST_SERIALIZATION_NVP(y);
				archive & BOOST_SERIALIZATION_NVP(z);
			}

		public:
			/**
			 * The coordinate on the X axis.
			 */
			Type x;

			/**
			 * The coordinate on the Y axis.
			 */
			Type y;

			/**
			 * The coordinate on the Z axis.
			 */
			Type z;

			/**
			 * Creates a new Vector3D.
			 */
			Vector3D() : Vector3D(0, 0, 0) {
			}

			/**
			 * Creates a new Vector3D.
			 * @param x The coordinate on the X axis.
			 * @param y The coordinate on the Y axis.
			 * @param z The coordinate on the Z axis.
			 */
			Vector3D(const Type& x, const Type& y, const Type& z) : x(x), y(y), z(z) {
			}

			/**
			 * Converts the Vector3D to a string.
			 * @return A string representation of the Vector3D.
			 */
			operator std::string() const {
				return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
			}

			/**
			 * Adds the values of the second Vector3D to this one.
			 * @param right The Vector3D to add.
			 * @return A reference to the modified object.
			 */
			Vector3D& operator +=(const Vector3D& right) {
				x += right.x;
				y += right.y;
				z += right.z;

				return *this;
			}

			/**
			 * Adds the values of the second Vector3D to the first one.
			 * @param left The Vector3D to modify.
			 * @param right The Vector3D to add.
			 * @return The modified Vector3D.
			 */
			friend Vector3D operator +(const Vector3D& left, const Vector3D& right) {
				return Vector3D(left) += right;
			}

			/**
			 * Subtracts the values of the second Vector3D from this one.
			 * @param right The Vector3D to subtract.
			 * @return A reference to the modified object.
			 */
			Vector3D& operator -=(const Vector3D& right) {
				x -= right.x;
				y -= right.y;
				z -= right.z;

				return *this;
			}

			/**
			 * Subtracts the values of the second Vector3D from the first one.
			 * @param left The Vector3D to modify.
			 * @param right The Vector3D to subtract.
			 * @return The modified Vector3D.
			 */
			friend Vector3D operator -(const Vector3D& left, const Vector3D& right) {
				return Vector3D(left) -= right;
			}

			/**
			 * Multiplies each axis of this Vector3D with a specified value.
			 * @param right The value to use for multiplication.
			 * @return A reference to the modified object.
			 */
			Vector3D& operator *=(const Type& right) {
				x *= right.x;
				y *= right.y;
				z *= right.z;

				return *this;
			}

			/**
			 * Multiplies the values of the Vector3D by the specified value.
			 * @param left The Vector3D to modify.
			 * @param right The value to multiply with.
			 * @return The modified Vector3D.
			 */
			friend Vector3D operator *(const Vector3D& left, const Type& right) {
				return Vector3D(left) *= right;
			}

			/**
             * Determines whether the Vector3Ds are equal.
             * @param left The first Vector3D.
             * @param left The second Vector3D.
			 * @return Whether the Vector3Ds are equal.
			 */
			friend bool operator ==(const Vector3D& left, const Vector3D& right) {
				return left.x == right.x && left.y == right.y && left.z == right.z;
			}
	};
}
