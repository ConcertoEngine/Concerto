////
//// Created by arthu on 19/08/2022.
////
//
//#Include <vector>
//#Include "NazaraRenderer.hpp"
//#Include "NazaraEvent.hpp"
//#Include "Nazara/Renderer.hpp"
//
//#Include "NazaraEvent.hpp"
//#Include "Event.hpp"
//#Include "Input.hpp"
//
//namespace Concerto::Ecs::System
//{
//	NazaraEvent::NazaraEvent(Nz::RenderWindow& renderWindow) : _window(renderWindow)
//	{
//
//	}
//
//	void NazaraEvent::PollEvents(float deltaTime)
//	{
//		Nz::WindowEvent event{};
//		std::vector<Event> events;
//		while (_window.PollEvent(&event))
//		{
//			switch (event.type)
//			{
//			case Nz::WindowEventType::Quit:
//			{
//				_window.Close();
//				break;
//			}
//			case Nz::WindowEventType::Resized:
//			{
//				Nz::Vector2ui windowSize = _window.GetSize();
//				auto projectionMatrix = Nz::Matrix4f::Perspective(Nz::DegreeAnglef(70.f),
//						float(windowSize.x) / windowSize.y, 0.1f, 1000.f);
////				for (auto& ubo: _ubos)
////				{
////					if (!ubo.has_value())
////						continue;
////					ubo.value().first.projectionMatrix = projectionMatrix;
////				}
//				break;
//			}
//			case Nz::WindowEventType::KeyPressed:
//			{
//				auto& e = events.emplace_back();
//				e.type = Event::Key;
//				KeyEvent keyEvent{};
//				keyEvent.key = (Key)event.key.virtualKey;
//				keyEvent.triggerType = TriggerType::Pressed;
//				e.data = keyEvent;
//				break;
//			}
//			case Nz::WindowEventType::KeyReleased:
//			{
//				auto& e = events.emplace_back();
//				e.type = Event::Key;
//				KeyEvent keyEvent{};
//				keyEvent.key = (Key)event.key.scancode;
//				keyEvent.triggerType = TriggerType::Released;
//				e.data = keyEvent;
//				break;
//			}
//			case Nz::WindowEventType::MouseButtonPressed:
//			{
//				auto& e = events.emplace_back();
//				e.type = Event::Mouse;
//				MouseEvent mouseEvent{};
//				MouseButton mouseButton{};
//				mouseButton.button = (MouseButton::Button)event.mouseButton.button;
//				mouseButton.clickCount = event.mouseButton.clickCount;
//				mouseButton.x = event.mouseButton.x;
//				mouseButton.y = event.mouseButton.y;
//				mouseButton.triggerType = TriggerType::Pressed;
//				mouseEvent.button = mouseButton;
//				mouseEvent.type = MouseEvent::Button;
//				e.data = mouseEvent;
//				break;
//			}
//			case Nz::WindowEventType::MouseButtonReleased:
//			{
//				auto& e = events.emplace_back();
//				e.type = Event::Mouse;
//				MouseEvent mouseEvent{};
//				MouseButton mouseButton{};
//				mouseButton.button = (MouseButton::Button)event.mouseButton.button;
//				mouseButton.clickCount = 0;
//				mouseButton.x = event.mouseButton.x;
//				mouseButton.y = event.mouseButton.y;
//				mouseButton.triggerType = TriggerType::Released;
//				mouseEvent.button = mouseButton;
//				mouseEvent.type = MouseEvent::Button;
//				e.data = mouseEvent;
//				break;
//			}
//			case Nz::WindowEventType::MouseWheelMoved:
//			{
//				auto& e = events.emplace_back();
//				e.type = Event::Mouse;
//				MouseEvent mouseEvent{};
//				MouseWheel mouseWheel{};
//				mouseWheel.x = event.mouseWheel.x;
//				mouseWheel.y = event.mouseWheel.y;
//				mouseWheel.delta = event.mouseWheel.delta;
//				mouseEvent.type = MouseEvent::Wheel;
//				mouseEvent.mouseWheel = mouseWheel;
//				e.data = mouseEvent;
//				break;
//			}
//			case Nz::WindowEventType::MouseMoved:
//			{
//				auto& e = events.emplace_back();
//				e.type = Event::Mouse;
//				MouseEvent mouseEvent{};
//				MouseMove mouseMove{};
//				mouseMove.x = event.mouseMove.x;
//				mouseMove.y = event.mouseMove.y;
//				mouseMove.deltaX = event.mouseMove.deltaX;
//				mouseMove.deltaY = event.mouseMove.deltaY;
//				mouseEvent.type = MouseEvent::Moved;
//				mouseEvent.mouseMove = mouseMove;
//				e.data = mouseEvent;
//				break;
//			}
//			default:
//				break;
//			}
//		}
//		Input::Instance().Trigger(events, deltaTime);
//	}
//} // Concerto