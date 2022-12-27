//
// Created by arthur on 26/12/2022.
//

#ifndef CONCERTO_MATCHER_HPP
#define CONCERTO_MATCHER_HPP

#include <set>
#include "Registry.hpp"

namespace Concerto::Ecs
{
	class Observer;

	/**
	 * @brief The Matcher class allows you to specify criteria for matching entities in a registry.
	 */
	class Matcher
	{
	public:
		/**
		 * Constructs a new Matcher for the given registry.
		 * @param registry The registry to match against.
		 */
		explicit Matcher(Registry& registry);

		/**
		 * @brief Constructs a new Matcher for the given registry.
		 * @param registry The registry to match against.
		 * @param observer observer An observer that will be notified when an entity is added or removed from the set of matching entities.
		 */
		Matcher(Registry& registry, Observer& observer);

		/**
		 * @brief Returns true if the given entity matches the criteria specified by the Matcher.
		 * @param entity The entity to test.
		 * @return True if the entity matches the criteria, false otherwise.
		 */
		[[nodiscard]] bool Matches(Entity::Id entity);

		/**
		 * @brief Specifies that the Matcher should match entities that have at least one of the given component types.
		 * @tparam T The type of the component.
		 * @return The Matcher object (for chaining).
		 */
		template<typename... Component>
		Matcher& AllOf()
		{
			(_allOf.insert(Ecs::Component::GetId<Component>()), ...);
			return *this;
		}

		/**
		 * @brief Specifies that the Matcher should not match entities that have any of the given component types.
		 * @tparam T The type of the component.
		 * @return The Matcher object (for chaining).
		 */
		template<typename... Component>
		Matcher& NoneOf()
		{
			(_noneOf.insert(Ecs::Component::GetId<Component>()), ...);
			return *this;
		}

		/**
		 * @brief Excludes the given entities from being matched.
		 * @tparam T The entity to be excluded.
		 * @return The Matcher object (for chaining).
		 */
		template<typename... Entities>
		Matcher& Exclude(Entities... entities)
		{
			(_excluded.insert(entities), ...);
			return *this;
		}

		/**
		 * @brief Specifies that the Matcher should only match the given entities.
		 * @tparam T The entity to be included.
		 * @return The Matcher object (for chaining).
		 */
		template<typename... Entities>
		Matcher& Only(Entities... entities)
		{
			(_only.insert(entities), ...);
			return *this;
		}

	private:
		Registry& _registry;
		Observer* _observer;
		std::set<Component::Id> _allOf;
		std::set<Component::Id> _noneOf;
		std::set<Entity::Id> _excluded;
		std::set<Entity::Id> _only;
		std::set<Entity::Id> _matchingEntities;
	};
} // Concerto::Ecs
#endif //CONCERTO_MATCHER_HPP
