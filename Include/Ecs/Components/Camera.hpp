//
// Created by arthur on 01/08/2022.
//

#ifndef CONCERTO_CAMERA_HPP
#define CONCERTO_CAMERA_HPP

#include "Concerto/Core/Math/Vector.hpp"
#include "Concerto/Core/Math/Quaternion.hpp"

namespace Concerto::Ecs
{
	struct Camera
	{
		Math::Vector3f Position;
		Math::Quaternionf Rotation;
	};
}
#endif //CONCERTO_CAMERA_HPP
