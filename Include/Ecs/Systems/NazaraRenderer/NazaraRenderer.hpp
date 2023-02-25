//
// Created by arthu on 01/08/2022.
//

#ifndef CONCERTO_NAZARARENDERER_HPP
#define CONCERTO_NAZARARENDERER_HPP

#include <array>
#include <chrono>
#include <memory>
#include <iostream>
#include <optional>
#include <thread>
#include <unordered_map>

#include "Mesh.hpp"
#include "Concerto/Core/Math/Transform.hpp"
#include "Concerto/Core/SparseArray.hpp"
#include "systems/System.hpp"

#include "NazaraEvent.hpp"
#include "Nazara/Core.hpp"
#include "Nazara/Math.hpp"
#include "Nazara/Platform.hpp"
#include "Nazara/Renderer.hpp"
#include "Nazara/Utility/Plugins/AssimpPlugin.hpp"
#include "Nazara/Graphics.hpp"
#include "NZSL/FilesystemModuleResolver.hpp"
#include "NZSL/LangWriter.hpp"
#include "NZSL/Parser.hpp"
#include "NZSL/Ast/SanitizeVisitor.hpp"
#include "Nazara/Utility.hpp"

namespace Concerto::Ecs::System
{
	struct UniformBufferObject
	{
		Nz::Matrix4f projectionMatrix;
		Nz::Matrix4f modelMatrix;
		Nz::Matrix4f viewMatrix;
	};

	class NazaraRenderer : public System
	{
	public:
		explicit NazaraRenderer(const Config::Object& data);

		~NazaraRenderer()  override = default;

		void Update(float deltaTime, Registry& r) override;

		void StepUpdate(float deltaTime, Registry& r) override;

		bool ShouldClose() const;

	private:
		void UpdateEvents(float deltaTime);

		std::string _assetPath;
		Nz::Application<Nz::Graphics> _app;
		std::shared_ptr<Nz::RenderDevice> _device;
		Nz::AppWindowingComponent& _windowing;
		Nz::Window& _window;
		Nz::WindowSwapchain _windowSwapchain;
	};
}
#endif //CONCERTO_NAZARARENDERER_HPP
