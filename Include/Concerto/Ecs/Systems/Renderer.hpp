//
// Created by arthur on 11/03/2023.
//

#ifndef CONCERTO_INCLUDE_ECS_SYSTEMS_RENDERER_HPP_
#define CONCERTO_INCLUDE_ECS_SYSTEMS_RENDERER_HPP_

#include "Concerto/Ecs/Systems/System.hpp"
#include "Concerto/Ecs/Matcher.hpp"

#include <Nazara/Core.hpp>
#include <Nazara/Graphics.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Platform.hpp>

namespace Concerto
{
	class Renderer : public System
	{
	 public:
		explicit Renderer(const Config::Object &data);

		virtual void Update(float deltaTime, Registry &r) override;

		Nz::WindowSwapchain& GetWindowSwapchain();
		const Nz::WindowSwapchain& GetWindowSwapchain() const;
		Nz::Window& GetWindow();

		bool ShouldClose() const;
		
		void SetViewerInstance(Nz::ViewerInstance& viewerInstance, Nz::Camera& camera);
	private:
		Nz::Application<Nz::Graphics> _app;
		std::shared_ptr<Nz::RenderDevice> _renderDevice;
		Nz::AppWindowingComponent* _windowing;
		Nz::Window* _window;
		Nz::WindowSwapchain _windowSwapchain;
		Nz::WorldInstancePtr _modelInstance;
		Nz::ElementRendererRegistry _elementRegistry;
		Nz::ForwardFramePipeline _framePipeline;
		std::size_t _worldInstanceIndex1;
		Nz::ViewerInstance* _viewerInstance;
	};
} // Concerto

#endif //CONCERTO_INCLUDE_ECS_SYSTEMS_RENDERER_HPP_
