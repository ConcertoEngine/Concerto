//
// Created by arthur on 26/12/2022.
//

#ifndef CONCERTO_MATCHER_HPP
#define CONCERTO_MATCHER_HPP

#include <set>
#include "Concerto/Ecs/Registry.hpp"

namespace Concerto
{
	/**
	 * @brief The Matcher class allows you to specify criteria for matching entities in a registry.
	 */
	class Matcher
	{
	public:
		Matcher() = default;
		/**
		 * Constructs a new Matcher for the given registry.
		 * @param registry The registry to match against.
		 */
		explicit Matcher(Registry& registry);

		/**
		 * @brief Sets the registry by replacing the existing one.
		 * @param registry The registry to match against.
		 */
		void SetRegistry(Registry& registry);

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
			(_allOf.insert(ComponentHelper::GetId<Component>()), ...);
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
			(_noneOf.insert(ComponentHelper::GetId<Component>()), ...);
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

		/**
		 * @bried Iterates over all matching entities and calls the given function.
		 * @tparam Func The type of the function.
		 */
		template<typename Func>
		requires std::invocable<Func, Registry&, Entity::Id>
		void ForEachMatching(Func&& func)
		{
			CONCERTO_ASSERT(_registry != nullptr && "Matcher::ForEachMatching: Registry is null");
			for (auto entity = 0; entity < _registry->GetEntityCount(); ++entity)
			{
				if (Matches(entity))
					func(*_registry, entity);
			}
		}
	private:
		Registry* _registry = nullptr;
		std::set<ComponentHelper::Id> _allOf;
		std::set<ComponentHelper::Id> _noneOf;
		std::set<Entity::Id> _excluded;
		std::set<Entity::Id> _only;
		std::set<Entity::Id> _matchingEntities;
	};
} // Concerto::Ecs
#endif //CONCERTO_MATCHER_HPP
