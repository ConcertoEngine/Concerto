//
// Created by arthur on 20/05/22.
//

#ifndef CONCERTO_WORLD_HPP
#define CONCERTO_WORLD_HPP

#include <memory>
#include <Concerto/Core/SparseVector.hpp>

#include "Concerto/Engine/Ecs/Export.hpp"
#include "Concerto/Engine/Ecs/Registry.hpp"
#include "Concerto/Engine/Ecs/Systems/System.hpp"

namespace Concerto
{
	/**
	 * @brief The World class is the main class of the ECS.
	 * It contains all the entities and Systems.
	 */
	class CONCERTO_ENGINE_ECS_API World
	{
	public:
		World() = default;

		World(World&&) noexcept = default;

		World(const World&) = delete;

		World& operator=(World&&) = delete;

		World& operator=(const World&) = delete;

		~World() = default;

		Registry& GetRegistry();

		void Update(float deltaTime);

		void StepUpdate(float deltaTime);

		/**
		 * @brief Add a system to the world.
		 * @tparam T The type of the system.
		 * @param args The arguments to construct the system.
		 * @return A reference to the system.
		 */
		template<typename T, typename... Args>
		T& AddSystem(Args&& ...args)
		{
			static_assert(std::is_base_of_v<System, T>, "T must inherit from System");
			auto id = System::GetId<T>();
			std::unique_ptr<System> systemPtr = std::make_unique<T>(std::forward<Args>(args)...);
			auto& system = _systems.Emplace(id, std::move(systemPtr));
			return static_cast<T&>(*system);
		}

		/**
		 * @brief Check if a system is in the world.
		 * @tparam T The type of the system.
		 * @return True if the system is in the world, false otherwise.
		 */
		template<typename T>
		[[nodiscard]] bool HasSystem() const
		{
			static_assert(std::is_base_of_v<System, T>, "T must inherit from System");
			return _systems.Has(System::GetId<T>());
		}

		/**
		 * @brief Get a system from the world.
		 * @tparam T The type of the system.
		 * @return A reference to the system.
		 * @throw std::runtime_error if the system is not in the world.
		 */
		template<typename T>
		T& GetSystem()
		{
			static_assert(std::is_base_of_v<System, T>, "T must inherit from System");
			if (!HasSystem<T>())
				throw std::runtime_error("System not found");
			auto id = System::GetId<T>();
			return *_systems[id];
		}

		/**
		 * @brief Remove a system from the world.
		 * @tparam T The type of the system.
		 * @throw std::runtime_error if the system is not in the world.
		 */
		template<typename T>
		void RemoveSystem()
		{
			static_assert(std::is_base_of_v<System, T>, "T must inherit from System");
			if (!HasSystem<T>())
				throw std::runtime_error("System not found");
			auto id = System::GetId<T>();
			_systems.Erase(id);
		}

	private:
		Registry _registry;
		SparseVector<std::unique_ptr<System>> _systems;
	};
}


#endif //CONCERTO_WORLD_HPP
