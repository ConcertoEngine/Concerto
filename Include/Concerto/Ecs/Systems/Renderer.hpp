//
// Created by arthur on 11/03/2023.
//

#ifndef CONCERTO_INCLUDE_ECS_SYSTEMS_RENDERER_HPP_
#define CONCERTO_INCLUDE_ECS_SYSTEMS_RENDERER_HPP_

#include "Concerto/Ecs/Systems/System.hpp"
#include "Concerto/Ecs/Matcher.hpp"

#include <Nazara/Core.hpp>
#include <Nazara/Graphics.hpp>
#include <Nazara/Platform/AppWindowingComponent.hpp>

namespace Nz
{
	class Nz::AppWindowingComponent;
}

namespace Concerto::Ecs::System
{
	class Renderer : public System
	{
	 public:
		explicit Renderer(const Config::Object &data);

		virtual void Update(float deltaTime, Registry &r) override;

		Nz::WindowSwapchain& GetWindowSwapchain();

		const Nz::WindowSwapchain& GetWindowSwapchain() const;

		bool ShouldClose() const;
	private:
		Nz::Application<Nz::Graphics> _app;
		Nz::AppWindowingComponent* _windowing;
		Nz::AppEntitySystemComponent* _ecsComponent;
		Nz::Window* _window;
		Nz::EnttWorld* _world;
		Nz::RenderSystem* _renderSystem;
		Nz::WindowSwapchain* _windowSwapchain;
	};
} // Concerto

#endif //CONCERTO_INCLUDE_ECS_SYSTEMS_RENDERER_HPP_
