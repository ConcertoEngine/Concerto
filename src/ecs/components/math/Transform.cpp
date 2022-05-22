//
// Created by arthur on 22/05/22.
//

#include "Transform.hpp"

void Concerto::Component::Math::Transform::translate(float x, float y, float z)
{
	Location.X() += x;
	Location.Y() += y;
	Location.Z() += z;
}

void Concerto::Component::Math::Transform::translate(const Concerto::Component::Math::Vector3f& vec)
{
	translate(vec.X(), vec.Y(), vec.Z());
}