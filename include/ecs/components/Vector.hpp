//
// Created by arthur on 22/05/22.
//

#ifndef CONCERTO_VECTOR_HPP
#define CONCERTO_VECTOR_HPP

#include <array>
#include <type_traits>

namespace Concerto::Component::Math
{
	/**
	 * @brief Vector class that represents a mathematical vector.
	 *
	 * @tparam T The type of the vector's data.
	 * @tparam Size The size of the vector
	 */
	template<typename T, std::size_t Size>
	class Vector
	{
	public:
		Vector() = default;

		template<typename... Args,
				typename = std::enable_if_t<sizeof...(Args) == Size>>
		explicit Vector(Args&&... args) : _data{ static_cast<T>(args)... }
		{
		}

		Vector(Vector&&) noexcept = default;

		Vector(const Vector&) = default;

		Vector& operator=(Vector&&) noexcept = default;

		Vector& operator=(const Vector&) = default;

		~Vector() = default;

		[[nodiscard]] const std::array<T, Size>& GetData() const;

		[[nodiscard]] constexpr std::size_t GetSize() const
		{
			return Size;
		}

		[[nodiscard]] constexpr T& X() const noexcept
		{
			static_assert(Size >= 1, "Error : Getting the X value require the vector size 1 or more");
			return const_cast<T&>(_data[0]);
		}

		[[nodiscard]] constexpr T& Y() const noexcept
		{
			static_assert(Size >= 2, "Error : Getting the Y value require the vector size 2 or more");
			return const_cast<T&>(_data[1]);
		}

		[[nodiscard]] constexpr T& Z() const noexcept
		{
			static_assert(Size >= 3, "Error : Getting the Z value require the vector size 3 or more");
			return const_cast<T&>(_data[2]);
		}

		constexpr Vector operator+(const Vector& vector) const noexcept;

		constexpr Vector operator+(T val) const noexcept;

		constexpr Vector operator-(const Vector& vector) const noexcept;

		constexpr Vector operator-(T val) const noexcept;

		constexpr Vector operator*(const Vector& vector) const noexcept;

		constexpr Vector operator*(T val) const noexcept;

		constexpr Vector operator/(const Vector& vector) const noexcept;

		constexpr Vector operator/(T val) const noexcept;

		constexpr Vector& operator+=(const Vector& vector) noexcept;

		constexpr Vector& operator+=(T val) noexcept;

		constexpr Vector& operator-=(const Vector& vector) noexcept;

		constexpr Vector& operator-=(T val) noexcept;

		constexpr Vector& operator*=(const Vector& vector) noexcept;

		constexpr Vector& operator*=(T val) noexcept;

		constexpr Vector& operator/=(const Vector& vector) noexcept;

		constexpr Vector& operator/=(T val) noexcept;

		constexpr const T& operator[](std::size_t index) const
		{
			return _data[index];
		}

		constexpr T& operator[](std::size_t index)
		{
			return _data[index];
		}

		constexpr bool operator==(const Vector& other) const noexcept;

		constexpr bool operator!=(const Vector& other) const noexcept
		{
			return *this != other;
		}

	private:
		std::array<T, Size> _data;
	};

	using Vector2i = Vector<int, 2>;
	using Vector2d = Vector<double, 2>;
	using Vector2f = Vector<float, 2>;

	using Vector3i = Vector<int, 3>;
	using Vector3d = Vector<double, 3>;
	using Vector3f = Vector<float, 3>;
}

#include "Vector.inl"
#endif //CONCERTO_VECTOR_HPP