//
// Created by arthur on 18/05/22.
//

#ifndef CONCERTO_COMPONENTHELPER_HPP
#define CONCERTO_COMPONENTHELPER_HPP

#include <cstddef>

namespace Concerto
{
	class ComponentHelper
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

#endif //CONCERTO_COMPONENTHELPER_HPP