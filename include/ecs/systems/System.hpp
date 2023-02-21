//
// Created by arthu on 01/08/2022.
//

#ifndef CONCERTO_SYSTEM_HPP
#define CONCERTO_SYSTEM_HPP

#include "Concerto/Core/Config.hpp"
#include "Registry.hpp"

namespace Concerto::Ecs::System
{
	/**
	 * @brief Interface for a system.
	 * Provides the logic to act on entities and it components.
	 */
	class System
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

		/**
		 * @brief Get the Id of the system T
		 * @tparam T The type of the system to get the Id
		 * @return The Id of the system T
		 */
		template<typename T>
		static Id GetId()
		{
			static const Id id = _nextId++;
			return id;
		}

	private:
		const Config::Object &_data;
		static inline int _nextId;
	};
}
#endif //CONCERTO_SYSTEM_HPP
