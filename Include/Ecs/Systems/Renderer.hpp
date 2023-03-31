//
// Created by arthur on 11/03/2023.
//

#ifndef CONCERTO_INCLUDE_ECS_SYSTEMS_RENDERER_HPP_
#define CONCERTO_INCLUDE_ECS_SYSTEMS_RENDERER_HPP_

#include "System.hpp"
#include <Concerto/Core/StructuredData.hpp>
#include <Concerto/Graphics/VulkanRenderer.hpp>
#include <Concerto/Graphics/ImGUI.hpp>
#include <Concerto/Graphics/Window/Input.hpp>

namespace Concerto::Ecs::System
{
	class Renderer : public System
	{
	 public:
		explicit Renderer(Graphics::RendererInfo rendererInfo, const Config::Object &data);
		virtual void Update(float deltaTime, Registry &r) override;

		bool ShouldClose() const;
	 private:
		Graphics::RendererInfo _rendererInfo;
		Graphics::GLFW3WindowPtr _window;
		Graphics::VulkanRenderer _renderer;
		Concerto::Graphics::ImGUI* imGui;
		Input _input;
		float _deltaTime = 0;
	};

} // Concerto

#endif //CONCERTO_INCLUDE_ECS_SYSTEMS_RENDERER_HPP_
