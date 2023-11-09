//
// Created by arthur on 11/03/2023.
//

#include <Concerto/Core/Math/Transform.hpp>
#include <Concerto/Core/Logger.hpp>
#include <entt/entt.hpp>
#include <Nazara/Graphics/Components/GraphicsComponent.hpp>
#include <Nazara/Utility/Components/NodeComponent.hpp>

#include "Concerto/Ecs/Systems/Renderer.hpp"

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
		_worldInstanceIndex1(_framePipeline.RegisterWorldInstance(_modelInstance)),
		_viewerInstance(nullptr)
	{
		_modelInstance->UpdateWorldMatrix(Nz::Matrix4f::Translate(Nz::Vector3f::Forward() * 2 + Nz::Vector3f::Left()));
		_window->GetEventHandler().OnEvent.Connect([&](const Nz::WindowEventHandler*, const Nz::WindowEvent& event)
			{
				switch (event.type)
				{
				case Nz::WindowEventType::KeyPressed:
				{
					break;
				}
				case Nz::WindowEventType::MouseMoved:
				{
					break;
				}
				case Nz::WindowEventType::Resized:
				{
					break;
				}
				default:
					break;
				}
			});
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
		Nz::Recti scissorBox(Nz::Vector2i::Zero(), Nz::Vector2i(_window->GetSize()));
		Matcher modelMatcher;
		modelMatcher.AllOf<Nz::Model>();
		modelMatcher.SetRegistry(r);
		modelMatcher.ForEachMatching([&](Registry& registry, Entity::Id entity)
		{
			auto& model = registry.GetComponent<Nz::Model>(entity);
			_framePipeline.RegisterRenderable(_worldInstanceIndex1, Nz::FramePipeline::NoSkeletonInstance, &model, 0xFFFFFFFF, scissorBox);
		});

		Matcher lightMatcher;
		lightMatcher.AllOf<Nz::DirectionalLight>();
		lightMatcher.SetRegistry(r);
		lightMatcher.ForEachMatching([&](Registry& registry, Entity::Id entity)
		{
			auto& light = registry.GetComponent<Nz::DirectionalLight>(entity);
			_framePipeline.RegisterLight(&light, 0xFFFFFFFF);
		});
		
		Nz::EulerAnglesf camAngles(0.f, 0.f, 0.f);
		Nz::Quaternionf camQuat(camAngles);
		Nz::Vector3f viewerPos = Nz::Vector3f::Zero();

		_viewerInstance->UpdateViewMatrix(Nz::Matrix4f::TransformInverse(viewerPos, camAngles));
		_viewerInstance->UpdateEyePosition(viewerPos);

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
		_framePipeline.RegisterViewer(&camera, 0, {});
	}

	Nz::Window& Renderer::GetWindow()
	{
		CONCERTO_ASSERT(_window != nullptr);
		return *_window;
	}
} // Concerto