//
// Created by arthur on 18/08/2022.
//

#ifndef CONCERTO_EVENT_HPP
#define CONCERTO_EVENT_HPP

#include <variant>
#include <string>
#include "Key.hpp"
namespace Concerto
{
	enum TriggerType
	{
		Pressed,
		Released,
		Held
	};

	struct KeyEvent
	{
		Key key;
		TriggerType triggerType;
	};

	struct MouseButton
	{
		enum Button
		{
			Left,
			Right,
			Middle,
			XButton1,
			XButton2
		};
		std::size_t clickCount;
		Button button;
		int x;
		int y;
		TriggerType triggerType;
	};

	struct MouseMove
	{
		int deltaX;
		int deltaY;
		int x;
		int y;
	};

	struct MouseWheel
	{
		float delta;
		int x;
		int y;
	};

	struct MouseEvent
	{
		enum Type
		{
			Button,
			Moved,
			Wheel
		};
		Type type;
		MouseButton button;
		MouseMove mouseMove;
		MouseWheel mouseWheel;
	};

	struct Event
	{
		enum Type
		{
			Key,
			Mouse,
			Custom
		};

		Type type;
		std::string name;
		std::variant<KeyEvent, MouseEvent, float, bool, int, std::string> data;
	};
}
#endif //CONCERTO_EVENT_HPP
