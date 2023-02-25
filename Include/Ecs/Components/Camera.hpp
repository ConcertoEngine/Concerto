//
// Created by arthur on 01/08/2022.
//

#ifndef CONCERTO_CAMERA_HPP
#define CONCERTO_CAMERA_HPP
#include "Concerto/Core/Math/Transform.hpp"
#include "Concerto/Core/Math/Matrix.hpp"

namespace Concerto::Ecs
{
	struct Camera
	{
		Math::Vector3f Position;
		Math::Vector3f EulerAngles;
	};
}
#endif //CONCERTO_CAMERA_HPP
