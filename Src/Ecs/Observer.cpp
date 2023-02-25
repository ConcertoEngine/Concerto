//
// Created by arthur on 26/12/2022.
//

#include "Observer.hpp"

namespace Concerto::Ecs
{

	Observer::Observer(Callback& callback) : _callback(callback)
	{

	}

	void Observer::OnMatch(const Matcher& matcher, Entity::Id entity, bool matched)
	{
		_callback(matcher, entity, matched);
	}
}