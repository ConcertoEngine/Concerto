//
// Created by arthur on 01/08/2022.
//

#ifndef CONCERTO_CAMERA_HPP
#define CONCERTO_CAMERA_HPP
#include "Transform.hpp"
#include "Matrix.hpp"

namespace Concerto::Ecs
{
	struct Camera
	{
		Math::Vector3f Position;
		Math::Vector3f EulerAngles;
	};
}
#endif //CONCERTO_CAMERA_HPP
