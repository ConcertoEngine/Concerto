//
// Created by arthur on 23/05/22.
//

#ifndef CONCERTO_GLFW3_HPP
#define CONCERTO_GLFW3_HPP

#include "AWindow.hpp"

namespace Concerto
{
	class GlfW3 : public AWindow
	{
	public:
		GlfW3(const std::string& title, unsigned int width, unsigned int height);

		GlfW3() = delete;

		GlfW3(GlfW3&&) = delete;

		GlfW3(const GlfW3&) = delete;

		GlfW3& operator=(GlfW3&&) = delete;

		GlfW3& operator=(const GlfW3&) = delete;

		~GlfW3() override = default;

		Math::Vector2i getCursorPosition() override;

		void setTitle(const std::string& title) override;

		void setIcon(const std::string& path) override;

		void setCursorVisible(bool visible) override;

		void setCursorPosition(int x, int y) override;

		void setCursorIcon(const std::string& path) override;

		void setCursorDisabled(bool disabled) override;

	private:
	};

} // Concerto

#endif //CONCERTO_GLFW3_HPP
