//
// Created by arthur on 03/09/2022.
//

#ifndef CONCERTO_QUATERNION_H
#define CONCERTO_QUATERNION_H

#include <iostream>
#include "Algorithm.hpp"
#include "Vector.hpp"

namespace Concerto::Math
{
	template<typename T>
	class Quaternion
	{
	public:
		Quaternion() = default;

		/**
		 * @brief Construct a new Quaternion object
		 *
		 * @param x The x axis
		 * @param y The y axis
		 * @param z The z axis
		 * @param w The w scalar
		 */
		constexpr Quaternion(T x, T y, T z, T w) noexcept: _scalar(w), _vector(x, y, z)
		{

		}

		/**
		 * @brief Construct a new Quaternion object
		 *
		 * @param x The x axis
		 * @param y The y axis
		 * @param z The z axis
		 */
		constexpr Quaternion(T x, T y, T z) noexcept: _scalar(0), _vector(0, 0, 0)
		{
			Set(x, y, z);
		}

		/**
		 * @brief Construct a new Quaternion object
		 *
		 * @param vector The vector
		 * @param scalar The scalar
		 */
		constexpr Quaternion(const Vector3<T>& vector, T scalar) noexcept: _scalar(scalar), _vector(vector)
		{

		}

		/**
		 * @brief Assign a new value to this quaternion
		 * @param vector The vector
		 * @return Quaternion& A reference to this quaternion
		 */
		Quaternion<T>& operator=(const Vector3<T>& vector) noexcept
		{
			Set(vector.X(), vector.Y(), vector.Z());
			return *this;
		}

		/**
		 * @brief Assign a new value to this quaternion
		 */
		void Set(T x, T y, T z) noexcept
		{
			T cosX = std::cos(ToRadians(x / 2));
			T cosY = std::cos(ToRadians(y / 2));
			T cosZ = std::cos(ToRadians(z / 2));

			T sinX = std::sin(ToRadians(x / 2));
			T sinY = std::sin(ToRadians(y / 2));
			T sinZ = std::sin(ToRadians(z / 2));

			_scalar = cosX * cosY * cosZ - sinX * sinY * sinZ;
			_vector.X() = sinX * cosY * cosZ + cosX * sinY * sinZ;
			_vector.Y() = cosX * sinY * cosZ - sinX * cosY * sinZ;
			_vector.Z() = cosX * cosY * sinZ + sinX * sinY * cosZ;
		}

		/**
		 * @brief Get the w scalar
		 * @return The reference to the w scalar
		 */
		T& W() noexcept
		{
			return _scalar;
		}

		/**
		 * @brief Get the x axis
		 * @return The x axis value
		 */
		constexpr T X() const noexcept
		{
			return _vector.X();
		}

		/**
		 * @brief Get the y axis
		 * @return The y axis value
		 */
		constexpr T Y() const noexcept
		{
			return _vector.Y();
		}

		/**
		 * @brief Get the z axis
		 * @return The z axis value
		 */
		constexpr T Z() const noexcept
		{
			return _vector.Z();
		}

		/**
		 * @brief Get the w scalar
		 * @return The w scalar value
		 */
		constexpr T W() const noexcept
		{
			return _scalar;
		}

		/**
		 * @brief Get the inverse of this quaternion
		 * @return Quaternion The inverse of this quaternion
		 */
		Quaternion<T> Inverse() const noexcept
		{
			return Quaternion<T>(-_vector.X(), -_vector.Y(), -_vector.Z(), -_scalar);
		}

		/**
		 * @brief Conjugate the vector by multiplying X, Y, Z, part by -1
		 * @return The quaternion's conjugate
		 */
		Quaternion<T> Conjugate() const noexcept
		{
			Quaternion<T> q = *this;
			q._vector = Vector3<T>(-q.X(), -q.Y(), -q.Z());
			return q;
		}

		/**
		 * @brief Add the given quaternion to the current one
		 * @param other The quaternion to add
		 * @return A new quaternion that is the sum of the two
		 */
		Quaternion<T> operator+(const Quaternion<T>& other) const noexcept
		{
			return Quaternion<T>(_vector + other._vector, _scalar + other._scalar);
		}

		/**
		 * @brief Subtract the given quaternion to the current one
		 * @param other The quaternion to subtract
		 * @return A new quaternion that is the subtraction of the two
		 */
		Quaternion<T> operator-(const Quaternion<T>& other) const noexcept
		{
			return Quaternion<T>(_vector - other._vector, _scalar - other._scalar);
		}

		/**
		 * @brief Multiply the given quaternion to the current one
		 * @param other The quaternion to multiply
		 * @return A new quaternion that is the multiplication of the two
		 */
		Quaternion<T> operator*(const Quaternion<T>& other) const noexcept
		{
			Quaternion<T> result;
			result._vector.X() =
					_scalar * other._vector.X() + other._scalar * _vector.X() + _vector.Y() * other._vector.Z() -
					_vector.Z() * other._vector.Y();
			result._vector.Y() =
					_scalar * other._vector.Y() + other._scalar * _vector.Y() + _vector.Z() * other._vector.X() -
					_vector.X() * other._vector.Z();
			result._vector.Z() =
					_scalar * other._vector.Z() + other._scalar * _vector.Z() + _vector.X() * other._vector.Y() -
					_vector.Y() * other._vector.X();
			result._scalar =
					_scalar * other._scalar - _vector.X() * other._vector.X() - _vector.Y() * other._vector.Y() -
					_vector.Z() * other._vector.Z();
			return result;
		}

		/**
		 * @brief Divide the given quaternion to the current one
		 * @param other The quaternion to divide
		 * @return A new quaternion that is the division of the two
		 */
		Quaternion<T> operator/(const Quaternion<T>& other) const noexcept
		{
			return *this * other.Inverse();
		}

		/**
		 * @brief Add the given value to the current quaternion
		 * @param value The value to add
		 * @return A new quaternion that is the sum of the quaternion and the value
		 */
		Quaternion<T> operator+(T value) const noexcept
		{
			return Quaternion<T>(_vector + value, _scalar + value);
		}

		/**
		 * @brief Subtract the given value to the current quaternion
		 * @param value The value to subtract
		 * @return A new quaternion that is the subtraction of the quaternion and the value
		 */

		Quaternion<T> operator-(T value) const noexcept
		{
			return Quaternion<T>(_vector - value, _scalar - value);
		}

		/**
		 * @brief Multiply the given value to the current quaternion
		 * @param value The value to multiply
		 * @return A new quaternion that is the multiplication of the quaternion and the value
		 */

		Quaternion<T> operator*(T value) const noexcept
		{
			return Quaternion<T>(_vector * value, _scalar * value);
		}

		/**
		 * @brief Divide the given value to the current quaternion
		 * @param value The value to divide
		 * @return A new quaternion that is the division of the quaternion and the value
		 */

		Quaternion<T> operator/(T value) const noexcept
		{
			return Quaternion<T>(_vector / value, _scalar / value);
		}

		/**
		 * @brief Add the given quaternion to the current one
		 * @param other The quaternion to add
		 * @return A reference to the current quaternion
		 */
		Quaternion<T>& operator+=(const Quaternion<T>& other) noexcept
		{
			_vector += other._vector;
			_scalar += other._scalar;
			return *this;
		}

		/**
		 * @brief Subtract the given quaternion to the current one
		 * @param other The quaternion to subtract
		 * @return A reference to the current quaternion
		 */
		Quaternion<T>& operator-=(const Quaternion<T>& other) noexcept
		{
			_vector -= other._vector;
			_scalar -= other._scalar;
			return *this;
		}

		/**
		 * @brief Multiply the given quaternion to the current one
		 * @param other The quaternion to multiply
		 * @return A reference to the current quaternion
		 */
		Quaternion<T>& operator*=(const Quaternion<T>& other) noexcept
		{
			*this = *this * other;
			return *this;
		}

		/**
		 * @brief Divide the given quaternion to the current one
		 * @param other The quaternion to divide
		 * @return A reference to the current quaternion
		 */
		Quaternion<T>& operator/=(const Quaternion<T>& other) noexcept
		{
			*this = *this / other;
			return *this;
		}

		/**
		 * @brief Apply the quaternion to the given vector3D
		 * @param vector The vector to apply the quaternion to
		 * @return A new vector that is the result of the quaternion application
		 */
		Vector3<T> operator*(const Vector3<T>& vector) const noexcept
		{
			Vector3<T> q(_vector);
			Vector3<T> uv = q.Cross(vector);
			Vector3<T> uuv = q.Cross(uv);
			uv *= T(2.0) * _scalar;
			uuv *= T(2.0);
			auto x = vector + uv + uuv;
			return x;
//			return Vector3<T>(-x.X(), -x.Y(), -x.Z());
		}

		/**
		 * @brief Check if the quaternion is equal to the given one
		 * @param other The quaternion to compare to
		 * @return True if the quaternion is equal to the given one, false otherwise
		 */
		bool operator==(const Quaternion<T>& other) const noexcept
		{
			return _vector == other._vector && _scalar == other._scalar;
		}

		/**
		 * @brief Check if the quaternion is not equal to the given one
		 * @param other The quaternion to compare to
		 * @return True if the quaternion is not equal to the given one, false otherwise
		 */
		bool operator!=(const Quaternion<T>& other) const noexcept
		{
			return !(*this == other);
		}

	private:
		T _scalar;
		Vector3<T> _vector;
	};

	// Aliases
	using Quaternionf = Quaternion<float>;
	using Quaterniond = Quaternion<double>;

	template<typename T>
	std::ostream& operator<<(std::ostream& stream, const Quaternion<T>& quaternion) noexcept
	{
		stream << "Quaternion(X: " << quaternion.X() << ", Y: " << quaternion.Y() << ", Z: " << quaternion.Z()
			   << ", W: " << quaternion.W() << ")";
		return stream;
	}
}

#endif //CONCERTO_QUATERNION_H
