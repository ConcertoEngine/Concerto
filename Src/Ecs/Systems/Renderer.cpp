//
// Created by arthur on 11/03/2023.
//

#include <Concerto/Core/Math/Transform.hpp>
#include <Concerto/Core/Logger.hpp>
#include <entt/entt.hpp>
#include <Nazara/Graphics/Components/GraphicsComponent.hpp>
#include <Nazara/Utility/Components/NodeComponent.hpp>

#include "Concerto/Ecs/Systems/Renderer.hpp"

namespace Concerto::Ecs::System
{
	template<typename Component>
	void AddToEnttRegistry(Registry& r, entt::registry& registry)
	{
		Matcher matcher(r);
		matcher.AllOf<Component>();

		matcher.SetRegistry(r);
		matcher.ForEachMatching([&](Registry&, Entity::Id id) {
			if (registry.valid(entt::entity(id)))
			{
				//check if the entity has already the component
				if (!registry.all_of<Component>(entt::entity(id)))
				{
					auto& component = r.GetComponent<Component>(id);
					registry.emplace<Component>(entt::entity(id), component);
				}
				else
				{
					
				}

			}
			else
			{
				entt::entity e = registry.create(entt::entity(id));
				auto& component = r.GetComponent<Component>(id);
				registry.emplace<Component>(e, component);
			}
		});
	}

	Renderer::Renderer(const Config::Object& data) :
		System(data),
		_app(),
		_windowing(&_app.AddComponent<Nz::AppWindowingComponent>()),
		_ecsComponent(&_app.AddComponent<Nz::AppEntitySystemComponent>()),
		_window(&_windowing->CreateWindow(Nz::VideoMode(1280, 720), "Concerto")),
		_world(&_ecsComponent->AddWorld<Nz::EnttWorld>()),
		_renderSystem(&_world->AddSystem<Nz::RenderSystem>()),
		_windowSwapchain(&_renderSystem->CreateSwapchain(*_window))
	{
	}

	void Renderer::Update(float deltaTime, Registry &r)
	{
		entt::registry& registry = _world->GetRegistry();
		registry.clear();
		AddToEnttRegistry<Nz::NodeComponent>(r, registry);
		AddToEnttRegistry<Nz::GraphicsComponent>(r, registry);
		AddToEnttRegistry<Nz::CameraComponent>(r, registry);
		
		_app.Update(Nz::Time::FromDuration(std::chrono::duration<float>(deltaTime)));
	}

	Nz::WindowSwapchain& Renderer::GetWindowSwapchain()
	{
		CONCERTO_ASSERT(_windowSwapchain);
		return *_windowSwapchain;
	}

	const Nz::WindowSwapchain& Renderer::GetWindowSwapchain() const
	{
		CONCERTO_ASSERT(_windowSwapchain);
		return *_windowSwapchain;
	}

	bool Renderer::ShouldClose() const
	{
		return false;
	}
} // Concerto