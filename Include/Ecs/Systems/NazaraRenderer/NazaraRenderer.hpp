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
#include <filesystem>

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

	struct GraphicalObject
	{
		Nz::Model model;
		std::shared_ptr<Nz::Mesh> mesh;
		std::shared_ptr<Nz::MaterialInstance> materialInstance;
	};

	class NazaraRenderer : public System
	{
	public:
		explicit NazaraRenderer(const Config::Object& data);

		~NazaraRenderer()  override = default;

		void Update(float deltaTime, Registry& r) override;

		void StepUpdate(float deltaTime, Registry& r) override;

		bool ShouldClose() const;

		GraphicalObject& CreateMeshIfNotExist(const std::string& path);
		std::shared_ptr<Nz::Texture> CreateTextureIfNotExist(const std::string& path);
		std::shared_ptr<Nz::MaterialInstance> CreateMaterialIfNotExist(const std::string& path);
	private:
		std::filesystem::path _assetsPath;
		// Nazara
		Nz::Application<Nz::Graphics> _app;
		std::shared_ptr<Nz::RenderDevice> _device;
		Nz::AppWindowingComponent& _windowing;
		Nz::Window& _window;
		Nz::WindowSwapchain _windowSwapchain;
		Nz::Camera _camera;
		Nz::ViewerInstance& _viewerInstance;
		Nz::WorldInstancePtr _modelInstance;
		Nz::Recti _windowScissorBox;
		Nz::ElementRendererRegistry _elementRegistry;
		Nz::ForwardFramePipeline _framePipeline;
		std::size_t _cameraIndex;
		std::size_t _worldInstanceIndex;

		std::unordered_map<std::string, GraphicalObject> _meshes;
		std::unordered_map<std::string, std::shared_ptr<Nz::Texture>> _textures;
	};
}
#endif //CONCERTO_NAZARARENDERER_HPP
