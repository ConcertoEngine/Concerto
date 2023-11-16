//
// Created by arthur on 26/12/2022.
//

#include <algorithm>
#include <cassert>

#include "Concerto/Engine/Ecs/Matcher.hpp"
#include "Concerto/Engine/Ecs/Entity.hpp"

namespace Concerto
{
	Matcher::Matcher(Registry& registry) : _registry(&registry)
	{
	}

	void Matcher::SetRegistry(Registry& registry)
	{
		_registry = &registry;
	}

	[[nodiscard]] bool Matcher::Matches(Entity::Id entity)
	{
		assert(_registry != nullptr);
		if (!_allOf.empty() && std::any_of(_allOf.begin(), _allOf.end(), [&](ComponentHelper::Id id)
			{
				return !_registry->HasComponent(entity, id);
			}))
		{
			_matchingEntities.erase(entity);
			return false;
		}
		if (!_noneOf.empty() && std::any_of(_noneOf.begin(), _noneOf.end(), [&](ComponentHelper::Id id)
		{
			return _registry->HasComponent(entity, id);
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
		if (_matchingEntities.find(entity) == _matchingEntities.end())
		{
			_matchingEntities.insert(entity);
		}
		return true;
	}
}