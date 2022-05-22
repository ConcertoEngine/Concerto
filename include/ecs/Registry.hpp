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
#include "SparseArray.hpp"

namespace Concerto::Ecs
{
	/**
	 * @brief The Registry class is the main class of the ECS.
	 * It is used to create entities and components.
	 */
	class Registry
	{
	public:
		using map_element = SparseArray<std::any>;
		using container_type = std::unordered_map<Component::Id, map_element>;
		using iterator = container_type::iterator;
		using const_iterator = container_type::const_iterator;

		Registry() = default;

		Registry(Registry&&) = default;

		Registry(const Registry&) = delete;

		Registry& operator=(Registry&&) = delete;

		Registry& operator=(const Registry&) = delete;

		~Registry() = default;

		iterator begin() noexcept
		{
			return _components.begin();
		}

		iterator end() noexcept
		{
			return _components.end();
		}

		const_iterator cbegin() const noexcept
		{
			return _components.cbegin();
		}

		const_iterator cend() const noexcept
		{
			return _components.cend();
		}

		/**
		 * @brief Creates a new entity.
		 * @return The new entity.
		 */
		Entity::Id createEntity()
		{
			Entity::Id id = _nextId++;
			return id;
		}

		/**
		 * @brief Add a component to an entity
		 * @tparam Comp The component type
		 * @tparam Args The arguments type used to construct the component
		 * @param entity The entity
		 * @param args The arguments to pass to the component constructor
		 * @return A reference to the component
		 */
		template<typename Comp, typename... Args>
		Comp& emplaceComponent(Entity::Id entity, Args&& ...args)
		{
			Component::Id id = Component::getId<Comp>();
			if (_components.find(entity) == _components.end())
			{
				auto it = _components.emplace(id, map_element());
				return std::any_cast<Comp&>(it.first->second.emplace(entity, std::forward<Args>(args)...));
			}
			auto& sparseArrayElement = _components.at(id).emplace(entity, std::forward<Args>(args)...);
			return std::any_cast<Comp&>(sparseArrayElement);
		}

		/**
		 * @brief Remove a component from an entity
		 * @tparam Comp The component type
		 * @param entity The entity to remove the component from
		 */
		template<typename Comp>
		void removeComponent(Entity::Id entity)
		{
			Component::Id id = Component::getId<Comp>();
			if (_components.find(id) != _components.end())
			{
				_components[id].erase(entity);
			}
			else throw std::runtime_error("Component not found");
		}

		/**
		 * @brief Get a component from an entity
		 * @tparam Comp The component type
		 * @param entity The entity to get the component from
		 * @return A reference to the component
		 */
		template<class Comp>
		Comp& getComponent(Entity::Id entity)
		{
			Component::Id id = Component::getId<Comp>();
			auto it = _components.find(id);
			if (it == _components.end())
				throw std::runtime_error("Component not found");
			if (!it->second.has(entity))
				throw std::runtime_error("Component not found");
			return std::any_cast<Comp&>(it->second[entity]);
		}

		/**
		 * @tparam Comp The component type
		 * @param entity The entity to check for the component
		 * @return True if the entity has the component, false otherwise
		 */
		template<typename Comp>
		bool hasComponent(Entity::Id entity) const
		{
			Component::Id id = Component::getId<Comp>();
			auto it = _components.find(id);
			return it == _components.end() && it->second.has(entity);
		}

		/**
		 * @brief Get the number of entities with a component
		 * @tparam Comp The component type
		 * @return The number of entities
		 */
		Entity::Id getEntityCount() const
		{
			return _nextId;
		}

	private:
		std::size_t _nextId = 0;
		container_type _components;
	};
}

#endif //CONCERTO_REGISTRY_HPP