//
// Created by arthur on 22/12/2022.
//

#ifndef CONCERTO_OBSERVER_HPP
#define CONCERTO_OBSERVER_HPP

#include <unordered_set>
#include <algorithm>
#include <functional>
#include "Entity.hpp"

namespace Concerto::Ecs
{
	class Registry;
	class Matcher;
	class Observer
	{
	public:
		using Callback = std::function<void(const Matcher&, Entity::Id, bool)>;
		explicit Observer(Callback& callback);
		void OnMatch(const Matcher& matcher, Entity::Id entity, bool matched);
	protected:
		Callback _callback;
	};
}

#endif //CONCERTO_OBSERVER_HPP
