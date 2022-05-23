//
// Created by arthur on 22/05/22.
//

#include "Vector.hpp"

namespace Concerto::Math
{
	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator+(const Vector& vector) const noexcept
	{
		auto res = *this;
		res += vector;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator+(T val) const noexcept
	{
		auto res = *this;
		res += val;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator-(const Vector& vector) const noexcept
	{
		auto res = *this;
		res -= vector;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator-(T val) const noexcept
	{
		auto res = *this;
		res -= val;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator*(const Vector& vector) const noexcept
	{
		auto res = *this;
		res *= vector;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator*(T val) const noexcept
	{
		auto res = *this;
		res *= val;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator/(const Vector& vector) const noexcept
	{
		auto res = *this;
		res /= vector;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size> Vector<T, Size>::operator/(T val) const noexcept
	{
		auto res = *this;
		res /= val;
		return res;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator+=(const Vector& vector) noexcept
	{
		for (int i = 0; i < std::min(Size, vector.GetSize()); ++i)
			_data[i] += vector[i];
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator+=(T val) noexcept
	{
		for (auto& x: _data)
			x += val;
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator-=(const Vector& vector) noexcept
	{
		for (int i = 0; i < std::min(Size, vector.GetSize()); ++i)
			_data[i] -= vector[i];
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator-=(T val) noexcept
	{
		for (auto& x: _data)
			x -= val;
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator*=(const Vector& vector) noexcept
	{
		for (int i = 0; i < std::min(Size, vector.GetSize()); ++i)
			_data[i] *= vector[i];
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator*=(T val) noexcept
	{
		for (auto& x: _data)
			x *= val;
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator/=(const Vector& vector) noexcept
	{
		for (int i = 0; i < std::min(Size, vector.GetSize()); ++i)
			_data[i] /= vector[i];
		return *this;
	}


	template<typename T, std::size_t Size>
	constexpr Vector<T, Size>& Vector<T, Size>::operator/=(T val) noexcept
	{
		for (auto& x: _data)
			x /= val;
		return *this;
	}

	template<typename T, std::size_t Size>
	constexpr bool Vector<T, Size>::operator==(const Vector& other) const noexcept
	{
		return _data == other.GetData();
	}

	template<typename T, std::size_t Size>
	const std::array<T, Size>& Vector<T, Size>::GetData() const
	{
		return _data;
	}
}