//
// Created by arthur on 02/03/2023.
//

#ifndef CONCERTO_INCLUDE_ECS_COMPONENTS_DIRECTIONALLIGHT_HPP_
#define CONCERTO_INCLUDE_ECS_COMPONENTS_DIRECTIONALLIGHT_HPP_

#include <Concerto/Core/Math/Quaternion.hpp>
#include <Concerto/Core/Math/Vector.hpp>
#include "Color.hpp"

namespace Concerto
{
	struct DirectionalLight
	{
		Color color;
		Math::Quaternionf rotation;
		Math::Vector3f direction;
	};
}

#endif //CONCERTO_INCLUDE_ECS_COMPONENTS_DIRECTIONALLIGHT_HPP_
