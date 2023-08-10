//
// Created by arthur on 02/03/2023.
//

#ifndef CONCERTO_INCLUDE_ECS_COMPONENTS_COLOR_HPP_
#define CONCERTO_INCLUDE_ECS_COMPONENTS_COLOR_HPP_

#include <Concerto/Core/Math/Vector.hpp>

namespace Concerto
{
	struct Color
	{
	 public:
		Color() = default;
		explicit Color(Math::Vector4f color);
		Color(float r, float g, float b, float a);
		Color(const Color&) = default;
		Color(Color&&) = default;
		Color& operator=(const Color&) = default;
		Color& operator=(Color&&) = default;

		/**
		 * @return A reference to the red component of the color
		 */
		[[nodiscard]] float& R();
		/**
		 * @return A reference to the green component of the color
		 */
		[[nodiscard]] float& G();
		/**
		 * @return A reference to the blue component of the color
		 */
		[[nodiscard]] float& B();
		/**
		 * @return A reference to the alpha component of the color
		 */
		[[nodiscard]] float& A();

		/**
		 * @return A copy to the red component of the color
		 */
		[[nodiscard]] float R() const;
		/**
		 * @return A copy to the green component of the color
		 */
		[[nodiscard]] float G() const;
		/**
		 * @return A copy to the blue component of the color
		 */
		[[nodiscard]] float B() const;
		/**
		 * @return A copy to the alpha component of the color
		 */
		[[nodiscard]] float A() const;
	 private:
		Math::Vector4f _color;
	};
}

#endif //CONCERTO_INCLUDE_ECS_COMPONENTS_COLOR_HPP_
