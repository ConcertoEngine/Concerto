//
// Created by arthur on 20/05/22.
//

#ifndef CONCERTO_WORLD_HPP
#define CONCERTO_WORLD_HPP

#include <memory>
#include "Registry.hpp"
#include "ISystem.hpp"

namespace Concerto::Ecs
{
	/**
	 * @brief The World class is the main class of the ECS.
	 * It contains all the entities and systems.
	 */
	class World
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

		template<typename T, typename... Args>
		T& AddSystem(Args&& ...args)
		{
			_systems.push_back(std::make_unique<T>(std::forward<Args>(args)...));
			return (static_cast<T&>(*_systems.back()));
		}

	private:
		Concerto::Ecs::Registry _registry;
		std::vector<std::unique_ptr<System::ISystem>> _systems;
	};
}


#endif //CONCERTO_WORLD_HPP
