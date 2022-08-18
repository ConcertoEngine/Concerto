//
// Created by arthu on 01/08/2022.
//

#ifndef CONCERTO_CAMERA_HPP
#define CONCERTO_CAMERA_HPP
#include "Transform.hpp"

namespace Concerto::Ecs
{
	struct Camera
	{
		Math::Transform transform;
	};
}
#endif //CONCERTO_CAMERA_HPP
