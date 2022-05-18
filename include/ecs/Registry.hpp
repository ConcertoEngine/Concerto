//
// Created by arthur on 18/05/22.
//

#ifndef CONCERTO_REGISTRY_HPP
#define CONCERTO_REGISTRY_HPP

#include <unordered_map>
#include <vector>
#include <any>
#include <bitset>
#include <exception>
#include "Component.hpp"
#include "Entity.hpp"

namespace Concerto::Ecs
{
	class Registry
	{
	public:
		Registry() = default;

		Registry(Registry&&) = default;

		Registry(const Registry&) = delete;

		Registry& operator=(Registry&&) = delete;

		Registry& operator=(const Registry&) = delete;

		~Registry() = default;

		Entity::Id createEntity()
		{
			Entity::Id id = _nextId++;
			_entities.emplace(id, Entity());
			return id;
		}

		template<typename Comp, typename... Args>
		Comp& emplaceComponent(Entity::Id id, Args&& ...args)
		{
			auto it = _entities.find(id);
			if (it == _entities.end())
				throw std::runtime_error("Entity does not exist");
			return it->second.emplaceComponent<Comp>(std::forward<Args>(args)...);
		}

		template<typename Comp>
		void removeComponent(Entity::Id id)
		{
			auto it = _entities.find(id);
			if (it == _entities.end())
				throw std::runtime_error("Entity does not exist");
			it->second.removeComponent<Comp>();
		}

		template<typename Comp>
		bool hasComponent(Entity::Id id) const
		{
			auto it = _entities.find(id);
			if (it == _entities.end())
				throw std::runtime_error("Entity does not exist");
			return it->second.hasComponent<Comp>();
		}

	private:
		std::size_t _nextId = 0;
		std::unordered_map<Entity::Id, Entity> _entities;
	};
}

#endif //CONCERTO_REGISTRY_HPP