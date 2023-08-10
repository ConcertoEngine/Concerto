//
// Created by arthur on 11/03/2023.
//

#ifndef CONCERTO_INCLUDE_ECS_SYSTEMS_RENDERER_HPP_
#define CONCERTO_INCLUDE_ECS_SYSTEMS_RENDERER_HPP_

#include <Concerto/Core/StructuredData.hpp>
#include <Concerto/Graphics/VulkanRenderer.hpp>
#include <Concerto/Graphics/ImGUI.hpp>
#include <Concerto/Graphics/Window/Input.hpp>

#include "Concerto/Ecs/Systems/System.hpp"
#include "Concerto/Ecs/Matcher.hpp"

namespace Concerto::Ecs::System
{
	class Renderer : public System
	{
	 public:
		explicit Renderer(const Config::Object &data, Graphics::RendererInfo rendererInfo);
		virtual void Update(float deltaTime, Registry &r) override;

		bool ShouldClose() const;
	 private:
		Graphics::RendererInfo _rendererInfo;
		Graphics::GLFW3WindowPtr _window;
		Graphics::VulkanRenderer _renderer;
		Concerto::Graphics::ImGUI* imGui;
		Input _input;
		float _deltaTime = 0;
		Matcher _transformMeshMatcher;
		Matcher _cameraMatcher;
	};

} // Concerto

#endif //CONCERTO_INCLUDE_ECS_SYSTEMS_RENDERER_HPP_
