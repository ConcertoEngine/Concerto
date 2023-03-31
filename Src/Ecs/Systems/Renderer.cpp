//
// Created by arthur on 11/03/2023.
//

#include <Concerto/Core/Math/Transform.hpp>
#include "Renderer.hpp"
#include "Matcher.hpp"
#include "Camera.hpp"

using namespace Concerto::Graphics;

namespace Concerto::Ecs::System
{
	Renderer::Renderer(Graphics::RendererInfo rendererInfo, const Config::Object& data) :
	System(data),
	_rendererInfo(std::move(rendererInfo)),
	_window(std::make_unique<GlfW3>(rendererInfo.applicationName, rendererInfo.width, rendererInfo.height)),
	_renderer(rendererInfo, *_window),
	imGui(_renderer.GetImGUIContext())
	{
		_window->RegisterCursorPosCallback([&](AWindow<GLFWwindow>& window, double x, double y)
		{
//		  imGui->UpdateMousePosition(x, y);
		  Concerto::MouseEvent mouseEvent{};
		  static double deltaX = 0, deltaY = 0;
		  deltaX = x - deltaX;
		  deltaY = y - deltaY;
		  mouseEvent.type = Concerto::MouseEvent::Moved;
		  mouseEvent.mouseMove.x = x;
		  mouseEvent.mouseMove.y = y;
		  mouseEvent.mouseMove.deltaX = deltaX;
		  mouseEvent.mouseMove.deltaY = deltaY;
		  Input::Instance().TriggerMouseEvent(mouseEvent, _deltaTime);
		  deltaX = x;
		  deltaY = y;
		});

		_window->RegisterMouseButtonCallback([&](AWindow<GLFWwindow>& window, int button, int action, int mods)
		{
//		  imGui->UpdateMouseButton(button, action == GLFW_PRESS);
		  Concerto::MouseEvent mouseEvent{};
		  mouseEvent.type = Concerto::MouseEvent::Button;
		  mouseEvent.button.button = Concerto::MouseButton::Button(button);
		  mouseEvent.button.triggerType = Concerto::TriggerType(action);
		  Input::Instance().TriggerMouseEvent(mouseEvent, _deltaTime);
		});

		_window->RegisterKeyCallback([&](AWindow<GLFWwindow>& window, Key key, int scancode, int action, int mods)
		{
		  Concerto::KeyEvent keyEvent{};
		  keyEvent.key = Concerto::Key(key);
		  keyEvent.triggerType = Concerto::TriggerType(action);
		  Input::Instance().TriggerKeyEvent(keyEvent, _deltaTime);
		});
	}

	void Renderer::Update(float deltaTime, Registry& r)
	{
		_deltaTime = deltaTime;
		_window->PopEvent();

		Matcher matcher(r);
		matcher.AllOf<Math::Transform, MeshPtr>();

		for (std::size_t i = 0; i < r.GetEntityCount(); ++i)
		{
			if (!matcher.Matches(i))
				continue;

			auto& transform = r.GetComponent<Math::Transform>(i);
			auto& mesh = r.GetComponent<MeshPtr>(i);
			_renderer.DrawObject(mesh, transform.GetLocation(), transform.GetRotation(), transform.GetScale());
		}

		Matcher cameraMatcher(r);
		cameraMatcher.AllOf<Graphics::Camera>();
		Graphics::Camera* cameraComponent = nullptr;
		for (std::size_t i = 0; i < r.GetEntityCount(); ++i)
		{
			if (!cameraMatcher.Matches(i))
				continue;
			auto &cam = r.GetComponent<Graphics::Camera>(i);
			cameraComponent = &cam;
		}
		if (cameraComponent == nullptr)
			return;
		_renderer.Draw(*cameraComponent);
	}

	bool Renderer::ShouldClose() const
	{
		return false;
	}
} // Concerto