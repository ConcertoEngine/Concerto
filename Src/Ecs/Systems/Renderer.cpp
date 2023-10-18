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
		_worldInstanceIndex1(_framePipeline.RegisterWorldInstance(_modelInstance))
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
		Nz::RenderFrame frame = _windowSwapchain.AcquireFrame();
		if (!frame)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			return;
		}

		//viewerInstance.UpdateViewMatrix(Nz::Matrix4f::TransformInverse(viewerPos, camAngles));
		//viewerInstance.UpdateEyePosition(viewerPos);

		_framePipeline.Render(frame);

		frame.Present();

		// On incrémente le compteur de FPS improvisé
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

	Nz::Window& Renderer::GetWindow()
	{
		CONCERTO_ASSERT(_window != nullptr);
		return *_window;
	}
} // Concerto