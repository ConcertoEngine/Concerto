//
// Created by arthur on 20/05/22.
//


#include "World.hpp"

namespace Concerto::Ecs
{
	void World::update(float deltaTime)
	{
		for (auto& system : _systems)
		{
			system->update(deltaTime);
		}
	}

	void World::stepUpdate(float deltaTime)
	{
		for (auto& system : _systems)
		{
			system->stepUpdate(deltaTime);
		}
	}

	Registry& World::getRegistry()
	{
		return _registry;
	}
}
