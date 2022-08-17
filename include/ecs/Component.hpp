//
// Created by arthur on 18/05/22.
//

#ifndef CONCERTO_COMPONENT_HPP
#define CONCERTO_COMPONENT_HPP

#include <cstddef>

namespace Concerto::Ecs
{
	class Component
	{
	public:
		using Id = std::size_t;

		template<typename T>
		static Id GetId()
		{
			static const Id id = _nextId++;
			return id;
		}

		static inline int _nextId;
	};
}

#endif //CONCERTO_COMPONENT_HPP