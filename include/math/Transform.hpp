//
// Created by arthur on 22/05/22.
//

#ifndef CONCERTO_TRANSFORM_HPP
#define CONCERTO_TRANSFORM_HPP
#include "Vector.hpp"
#include "Quaternion.hpp"

namespace Concerto::Math
{
	class Transform
	{
	public:
		Transform() = default;
		Transform(const Vector3f& location, const Quaternionf& rotation, const Vector3f& scale) :
				Location(location),
				Rotation(rotation),
				Scale(scale)
		{
		}
		Transform(Transform&&) = default;
		Transform(const Transform&) = default;
		Transform& operator=(Transform&&) = default;
		Transform& operator=(const Transform&) = default;
		~Transform() = default;

		void translate(float x, float y, float z);

		void translate(const Vector3f& vec);
		bool operator==(const Transform& other) const;
		Vector3f Location;
		Quaternionf Rotation;
		Vector3f Scale;
	};
}
#endif //CONCERTO_TRANSFORM_HPP