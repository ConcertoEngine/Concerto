//
// Created by arthur on 18/05/22.
//

#ifndef CONCERTO_ENTITY_HPP
#define CONCERTO_ENTITY_HPP

#include <cstddef>
#include <exception>
#include <any>
#include <unordered_map>
#include <bitset>
#include <stdexcept>
#include "Component.hpp"

namespace Concerto::Ecs
{
	class Entity
	{
	public:
		using Id = std::size_t;

		Entity() = default;

		Entity(Entity&&) = default;

		Entity(const Entity&) = delete;

		Entity& operator=(Entity&&) = delete;

		Entity& operator=(const Entity&) = delete;

		template<typename Comp, typename... Args>
		Comp& emplaceComponent(Args&& ...args)
		{
			Component::Id id = Component::getId<Comp>();
			auto it = _components.find(id);
			if (it != _components.end())
				throw std::runtime_error("Component already exists");
			auto any = std::make_any<Comp>(std::forward<Args>(args)...);
			auto newElement = _components.emplace(id, any);
			_instanciatedComponents[id] = true;
			return std::any_cast<Comp&>(std::get<0>(newElement)->second);
		}

		template<typename Comp>
		void removeComponent()
		{
			Component::Id id = Component::getId<Comp>();
			auto it = _components.find(id);
			if (it == _components.end())
				throw std::runtime_error("Component does not exist");
			_instanciatedComponents[id] = false;
			_components.erase(it);
		}

		template<typename Comp>
		bool hasComponent() const
		{
			Component::Id id = Component::getId<Comp>();
			return _instanciatedComponents[id];
		}

	private:
		std::bitset<64> _instanciatedComponents{};
		std::unordered_map<Component::Id, std::any> _components{};
	};

}

#endif //CONCERTO_ENTITY_HPP