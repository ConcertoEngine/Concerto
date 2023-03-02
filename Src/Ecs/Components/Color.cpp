//
// Created by arthur on 02/03/2023.
//

#include "Color.hpp"

namespace Concerto
{

	Color::Color(Math::Vector4f color) : _color(std::move(color))
	{

	}

	Color::Color(float r, float g, float b, float a) : _color(r, g, b, a)
	{

	}

	float& Color::R()
	{
		return _color[0];
	}

	float& Color::G()
	{
		return _color[1];
	}

	float& Color::B()
	{
		return _color[2];
	}

	float& Color::A()
	{
		return _color[3];
	}

	float Color::R() const
	{
		return _color[0];
	}

	float Color::G() const
	{
		return _color[1];
	}

	float Color::B() const
	{
		return _color[2];
	}

	float Color::A() const
	{
		return _color[3];
	}
}