//
// Created by arthu on 01/08/2022.
//

#ifndef CONCERTO_SYSTEM_HPP
#define CONCERTO_SYSTEM_HPP

#include <Concerto/Core/Config.hpp>

#include "Concerto/Engine/Ecs/Export.hpp"
#include "Concerto/Engine/Ecs/Registry.hpp"

namespace Concerto
{
	/**
	 * @brief Interface for a system.
	 * Provides the logic to act on entities and it Components.
	 */
	class CONCERTO_ENGINE_ECS_API System
	{
	public:
		using Id = std::size_t;

		explicit System(const Config::Object &data) : _data(data) {}

		virtual ~System() = default;

		/**
		 * @brief This function is called every frame.
		 * @param deltaTime The time since the last Update
		 * @param r The registry of the world
		 */

		virtual void Update(float deltaTime, Registry &r) {};
		/**
		 * @brief This function is frame rate independent. It is used for physics calculations.
		 * The time between each call is 0.02 seconds. (50 calls per second)
		 * @param deltaTime The time since the last Update
		 * @param r The registry of the world
		 */
		virtual void StepUpdate(float deltaTime, Registry &r) {};
	private:
		const Config::Object &_data;
		static inline int _nextId;
	};
}
#endif //CONCERTO_SYSTEM_HPP
