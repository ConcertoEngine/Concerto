//
// Created by arthur on 11/03/2023.
//

#include <Concerto/Core/Math/Transform.hpp>
#include <Concerto/Core/Logger.hpp>
#include <entt/entt.hpp>
#include <Nazara/Graphics/Components/GraphicsComponent.hpp>
#include <Nazara/Utility/Components/NodeComponent.hpp>

#include "Concerto/Engine/Graphics/Renderer.hpp"

namespace Concerto
{
	Renderer::Renderer(const Config::Object& data) :
		System(data),
		_app(),
		_renderDevice(Nz::Graphics::Instance()->GetRenderDevice()),
		_windowing(&_app.AddComponent<Nz::AppWindowingComponent>()),
		_window(&_windowing->CreateWindow(Nz::VideoMode(1280, 720), "Concerto")),
		_windowSwapchain(_renderDevice, *_window),
		_modelInstance(std::make_shared<Nz::WorldInstance>()),
		_elementRegistry(),
		_framePipeline(_elementRegistry),
		_viewerInstance(nullptr)
	{
		_modelInstance->UpdateWorldMatrix(Nz::Matrix4f::Translate(Nz::Vector3f::Forward() * 2 + Nz::Vector3f::Left()));
	}

	void Renderer::Update(float deltaTime, Registry &r)
	{
		if (_viewerInstance == nullptr)
		{
			CONCERTO_ASSERT_FALSE;
			Logger::Debug("ViewerInstance is not set, skipping rendering, please set it with Renderer::SetViewerInstance");
			return;
		}

		Nz::RenderFrame frame = _windowSwapchain.AcquireFrame();
		if (!frame)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			return;
		}
		const Nz::Recti scissorBox(Nz::Vector2i::Zero(), Nz::Vector2i(_window->GetSize()));
		Matcher modelMatcher(r);
		modelMatcher.AllOf<Nz::Model, WorldInstanceIndex>();
		modelMatcher.ForEachMatching([&](Registry& registry, Entity::Id entity)
		{
			const auto& model = registry.GetComponent<Nz::Model>(entity);
			const auto& [index] = registry.GetComponent<WorldInstanceIndex>(entity);
			_framePipeline.RegisterRenderable(index, Nz::FramePipeline::NoSkeletonInstance, &model, 0xFFFFFFFF, scissorBox);
		});

		modelMatcher = Matcher(r);
		modelMatcher.AllOf<Nz::Model>().NoneOf<WorldInstanceIndex>();
		modelMatcher.ForEachMatching([&](Registry& registry, Entity::Id entity)
		{
			const auto& model = registry.GetComponent<Nz::Model>(entity);
			WorldInstanceIndex worldInstanceIndex = {_framePipeline.RegisterWorldInstance(_modelInstance)};
			registry.EmplaceComponent<WorldInstanceIndex>(entity, worldInstanceIndex);
			_framePipeline.RegisterRenderable(worldInstanceIndex.index, Nz::FramePipeline::NoSkeletonInstance, &model, 0xFFFFFFFF, scissorBox);
		});

		modelMatcher = Matcher(r);
		modelMatcher.AllOf<Nz::GraphicsComponent>().NoneOf<WorldInstanceIndex>();
		modelMatcher.ForEachMatching([&](Registry& registry, Entity::Id entity)
		{
			const auto& gfxComponent = registry.GetComponent<Nz::GraphicsComponent>(entity);
			auto& renderables = gfxComponent.GetRenderables();
			WorldInstanceIndex worldInstanceIndex = { _framePipeline.RegisterWorldInstance(_modelInstance) };
			registry.EmplaceComponent<WorldInstanceIndex>(entity, worldInstanceIndex);
			for (auto& renderable : renderables)
			{
				if (renderable.renderable == nullptr)
					continue;
				_framePipeline.RegisterRenderable(worldInstanceIndex.index, Nz::FramePipeline::NoSkeletonInstance, renderable.renderable.get(), 0xFFFFFFFF, scissorBox);
			}
		});

		modelMatcher = Matcher(r);
		modelMatcher.AllOf<Nz::GraphicsComponent, WorldInstanceIndex>();
		modelMatcher.ForEachMatching([&](Registry& registry, Entity::Id entity)
		{
			const auto& gfxComponent = registry.GetComponent<Nz::GraphicsComponent>(entity);
			auto& renderables = gfxComponent.GetRenderables();
			const auto& worldInstanceIndex = registry.GetComponent<WorldInstanceIndex>(entity);
			for (auto& renderable : renderables)
			{
				if (renderable.renderable == nullptr)
					continue;
				_framePipeline.RegisterRenderable(worldInstanceIndex.index, Nz::FramePipeline::NoSkeletonInstance, renderable.renderable.get(), 0xFFFFFFFF, scissorBox);
			}
		});

		Matcher lightMatcher(r);
		lightMatcher.AllOf<Nz::DirectionalLight>();
		lightMatcher.ForEachMatching([&](Registry& registry, Entity::Id entity)
		{
			const auto& light = registry.GetComponent<Nz::DirectionalLight>(entity);
			_framePipeline.RegisterLight(&light, 0xFFFFFFFF);
		});
		
		_framePipeline.Render(frame);

		frame.Present();

		_window->SetTitle("Concerto - " + std::to_string(1000.f / deltaTime));
		_app.Update(Nz::Time::FromDuration(std::chrono::duration<float>(deltaTime)));
	}

	Nz::WindowSwapchain& Renderer::GetWindowSwapchain()
	{
		return _windowSwapchain;
	}

	const Nz::WindowSwapchain& Renderer::GetWindowSwapchain() const
	{
		return _windowSwapchain;
	}

	bool Renderer::ShouldClose() const
	{
		return false;
	}

	void Renderer::SetViewerInstance(Nz::ViewerInstance& viewerInstance, Nz::Camera& camera)
	{
		if (_viewerInstance != nullptr)
			_framePipeline.UnregisterViewer(0);
		_viewerInstance = &viewerInstance;
		_framePipeline.RegisterViewer(&camera, 0);
	}

	Nz::Window& Renderer::GetWindow()
	{
		CONCERTO_ASSERT(_window != nullptr);
		return *_window;
	}
} // Concerto