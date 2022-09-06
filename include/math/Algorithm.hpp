//
// Created by arthur on 04/09/2022.
//

#ifndef CONCERTO_ALGORITHM_HPP
#define CONCERTO_ALGORITHM_HPP

namespace Concerto::Math
{
	/**
	 * @brief The Pi constant
	 * @tparam T The type of the constant

	 */
	template<typename T>
	constexpr T Pi = T(3.1415926535897932384626433832795);

	/**
	 * @brief Convert degrees to radians
	 * @param degrees The degrees
	 * @return T The radians
	 */
	template<typename T>
	constexpr T ToRadians(T degrees) noexcept
	{
		return degrees * Pi<T> / 180;
	}

}
#endif //CONCERTO_ALGORITHM_HPP
