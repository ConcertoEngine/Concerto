//
// Created by arthur on 22/05/22.
//

#include "Registry.hpp"


#ifndef CONCERTO_ISYSTEM_HPP
#define CONCERTO_ISYSTEM_HPP

namespace Concerto::Ecs::System
{
	/**
	 * @brief Interface for a system.
	 * Provides the logic to act on entities and it components.
	 */
	class ISystem
	{
	public:
		virtual ~ISystem() = default;

		/**
		 * @brief This function is called every frame.
		 * @param deltaTime The time since the last update
		 * @param r The registry of the world
		 */
		virtual void update(float deltaTime, Registry &r) = 0;
		/**
		 * @brief This function is frame rate independent. It is used for physics calculations.
		 * The time between each call is 0.02 seconds. (50 calls per second)
		 * @param deltaTime The time since the last update
		 * @param r The registry of the world
		 */
		virtual void stepUpdate(float deltaTime, Registry &r) = 0;
	};
}

#endif //CONCERTO_ISYSTEM_HPP