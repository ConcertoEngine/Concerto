//
// Created by arthur on 22/05/22.
//

#ifndef CONCERTO_TRANSFORM_HPP
#define CONCERTO_TRANSFORM_HPP
#include "Vector.hpp"

namespace Concerto::Math
{
	class Transform
	{
	public:

		Transform(const Vector3f& location, const Vector3f& rotation, const Vector3f& scale) :
				Location(location),
				Rotation(rotation),
				Scale(scale)
		{
		}

		Transform(Transform&&) = default;

		Transform(const Transform&) = default;

		~Transform() = default;

		void translate(float x, float y, float z);

		void translate(const Vector3f& vec);
		bool operator==(const Transform& other) const;
		Vector3f Location;
		Vector3f Rotation; // TODO Quaternion
		Vector3f Scale;
	};
}
#endif //CONCERTO_TRANSFORM_HPP