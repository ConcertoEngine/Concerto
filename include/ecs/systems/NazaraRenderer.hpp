//
// Created by arthu on 01/08/2022.
//

#ifndef CONCERTO_NAZARARENDERER_HPP
#define CONCERTO_NAZARARENDERER_HPP

#include <memory>
#include <array>
#include <chrono>
#include <iostream>
#include <thread>
#include <unordered_map>

#include "Mesh.hpp"
#include "Transform.hpp"

#include "systems/ASystem.hpp"

#include "Nazara/Core.hpp"
#include "Nazara/Math.hpp"
#include "Nazara/Platform.hpp"
#include "Nazara/Renderer.hpp"
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

	class NazaraRenderer : public ASystem
	{
	public:
		NazaraRenderer(const Config::Object& data);

		~NazaraRenderer() override = default;

		void update(float deltaTime, Registry& r) override;

		void stepUpdate(float deltaTime, Registry& r) override;

	private:
		void updateEvents();
		Nz::Mesh &createMeshIfNotExist(const Mesh &mesh, const Math::Transform &transform);
		Nz::Texture &createTextureIfNotExist(const Mesh &mesh);
		std::string _assetPath;
		UniformBufferObject _ubo;
		bool _uboUpdate = true;
		Nz::EulerAnglesf _camAngles;
		Nz::Quaternionf _camQuat;
		Nz::Clock updateClock;
		Nz::Clock secondClock;
		unsigned int fps = 0;
		Nz::Vector3f viewerPos = Nz::Vector3f::Zero();

		Nz::Renderer::Config _rendererConfig;
		Nz::RenderWindow _window;
		Nz::RenderPipelineLayoutInfo _pipelineLayoutInfo;
		Nz::ShaderBindingPtr _viewerShaderBinding;
		Nz::ShaderBindingPtr _textureShaderBinding;
		Nz::Vector2ui _windowSize;
		Nz::ShaderBindingPtr viewerShaderBinding;
		Nz::ShaderBindingPtr textureShaderBinding;

		nzsl::Ast::ModulePtr _shaderModule;
		nzsl::ShaderWriter::States _states;

		std::unique_ptr<Nz::Modules<Nz::Renderer>> _nazara;

		std::shared_ptr<Nz::RenderDevice> _device;
		std::shared_ptr<Nz::RenderPipelineLayout> _basePipelineLayout;
		std::shared_ptr<Nz::RenderPipelineLayout> _renderPipelineLayout;
		std::shared_ptr<Nz::RenderBuffer> _uniformBuffer;
		std::shared_ptr<Nz::ShaderModule> _fragVertShader;
		std::shared_ptr<Nz::CommandPool> _commandPool;
		std::shared_ptr<Nz::RenderPipeline> _pipeline;

		std::unordered_map<std::string, std::shared_ptr<Nz::Mesh>> _meshes;
		std::unordered_map<std::string, std::shared_ptr<Nz::Texture>> _textures;
	};
}
#endif //CONCERTO_NAZARARENDERER_HPP
