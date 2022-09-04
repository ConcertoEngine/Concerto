//
// Created by arthur on 03/09/2022.
//

#ifndef CONCERTO_QUATERNION_H
#define CONCERTO_QUATERNION_H

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
		constexpr Quaternion(T x, T y, T z, T w) noexcept: _scalar(w), _vector( x, y, z)
		{

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
			return Quaternion<T>(
					_vector * other._scalar + other._vector * _scalar + _vector.Cross(other._vector),
					_scalar * other._scalar - _vector.Dot(other._vector)
			);
		}

		/**
		 * @brief Divide the given quaternion to the current one
		 * @param other The quaternion to divide
		 * @return A new quaternion that is the division of the two
		 */
		Quaternion<T> operator/(const Quaternion<T>& other) const noexcept
		{
			return Quaternion<T>(
					_vector * other._scalar - other._vector * _scalar - _vector.Cross(other._vector),
					_scalar * other._scalar + _vector.Dot(other._vector)
			);
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
			_vector = _vector * other._scalar + other._vector * _scalar + _vector.Cross(other._vector);
			_scalar = _scalar * other._scalar - _vector.Dot(other._vector);
			return *this;
		}

		/**
		 * @brief Divide the given quaternion to the current one
		 * @param other The quaternion to divide
		 * @return A reference to the current quaternion
		 */
		Quaternion<T>& operator/=(const Quaternion<T>& other) noexcept
		{
			_vector = _vector * other._scalar - other._vector * _scalar - _vector.Cross(other._vector);
			_scalar = _scalar * other._scalar + _vector.Dot(other._vector);
			return *this;
		}

		/**
		 * @brief Apply the quaternion to the given vector3D
		 * @param vector The vector to apply the quaternion to
		 * @return A new vector that is the result of the quaternion application
		 */
		Vector3<T> operator*(const Vector3<T>& vector) const noexcept
		{
			return Vector3<T>(
					_vector.Cross(vector * T(2.0) + _vector.Cross(vector)) * _scalar + vector
			);
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
			return _vector != other._vector || _scalar != other._scalar;
		}
	private:
		T _scalar;
		Vector3<T> _vector;
	};

	// Aliases
	using Quaternionf = Quaternion<float>;
	using Quaterniond = Quaternion<double>;
}

#endif //CONCERTO_QUATERNION_H
