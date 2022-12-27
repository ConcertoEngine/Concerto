//
// Created by arthur on 26/12/2022.
//

#include <algorithm>
#include "Matcher.hpp"
#include "Entity.hpp"
#include "Observer.hpp"

namespace Concerto::Ecs
{
	Matcher::Matcher(Registry& registry) : _registry(registry), _observer(nullptr)
	{
	}

	Matcher::Matcher(Registry& registry, Observer& observer) : _registry(registry), _observer(&observer)
	{
	}

	[[nodiscard]] bool Matcher::Matches(Entity::Id entity)
	{
		if (!_allOf.empty() && std::any_of(_allOf.begin(), _allOf.end(), [&](Component::Id id)
		{
			return !_registry.HasComponent(entity, id);
		}))
		{
			_matchingEntities.erase(entity);
			return false;
		}
		if (!_noneOf.empty() && std::any_of(_noneOf.begin(), _noneOf.end(), [&](Component::Id id)
		{
			return _registry.HasComponent(entity, id);
		}))
		{
			_matchingEntities.erase(entity);
			return false;
		}
 		if (!_only.empty() && std::find(_only.begin(), _only.end(), entity) == _only.end())
		{
			_matchingEntities.erase(entity);
			return false;
		}
		if (!_excluded.empty() && std::find(_excluded.begin(), _excluded.end(), entity) != _excluded.end())
		{
			_matchingEntities.erase(entity);
			return false;
		}
		if (_observer && _matchingEntities.find(entity) == _matchingEntities.end())
		{
			_observer->OnMatch(*this, entity, true);
			_matchingEntities.insert(entity);
		}
		return true;
	}
}