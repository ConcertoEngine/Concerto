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
#include "Transform.hpp"
#include "SparseArray.hpp"
#include "systems/ASystem.hpp"

#include "NazaraEvent.hpp"
#include "Nazara/Core.hpp"
#include "Nazara/Math.hpp"
#include "Nazara/Platform.hpp"
#include "Nazara/Renderer.hpp"
#include "NZSL/FilesystemModuleResolver.hpp"
#include "Nazara/Utility/Plugins/AssimpPlugin.hpp"
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

		void Update(float deltaTime, Registry& r) override;

		void StepUpdate(float deltaTime, Registry& r) override;

		bool ShouldClose() const;

	private:
		void UpdateEvents(float deltaTime);

		bool _shouldClose;

		void CreateUbo(Entity::Id entity, const Math::Transform& transform, Nz::UploadPool &uploadPool);
		void UpdateUbo(Entity::Id entity, const Math::Transform& transform);
		Nz::Mesh& CreateMeshIfNotExist(Entity::Id entity, const Mesh& mesh, const Math::Transform& transform);

		Nz::Texture& CreateTextureIfNotExist(const Mesh& mesh);

		std::string _assetPath;
		UniformBufferObject _ubo;
		Nz::EulerAnglesf _camAngles;
		Nz::Quaternionf _camQuat;
		Nz::Vector3f viewerPos = Nz::Vector3f::Zero();

		Nz::Renderer::Config _rendererConfig;
		Nz::RenderWindow _window;
		Nz::RenderPipelineLayoutInfo _pipelineLayoutInfo;
		Nz::Vector2ui _windowSize;

		nzsl::Ast::ModulePtr _shaderModule;
		nzsl::ShaderWriter::States _states;

		std::unique_ptr<Nz::Modules<Nz::Renderer>> _nazara;
		std::optional<Nz::Plugin<Nz::AssimpPlugin>> _assimpPlugin;

		std::shared_ptr<Nz::RenderDevice> _device;
		Nz::ShaderBindingPtr _textureShaderBinding;
		std::shared_ptr<Nz::RenderPipelineLayout> _basePipelineLayout;
		std::shared_ptr<Nz::RenderPipelineLayout> _renderPipelineLayout;
		std::shared_ptr<Nz::ShaderModule> _fragVertShader;
		std::shared_ptr<Nz::CommandPool> _commandPool;
		std::shared_ptr<Nz::RenderPipeline> _pipeline;
		std::shared_ptr<Nz::TextureSampler> _textureSampler;

		std::unordered_map<std::string, std::shared_ptr<Nz::Mesh>> _meshes;
		std::unordered_map<std::string, std::shared_ptr<Nz::Texture>> _textures;

		SparseArray<std::pair<UniformBufferObject, Nz::ShaderBindingPtr>> _ubos;
		SparseArray<std::shared_ptr<Nz::RenderBuffer>> _uniformBuffers;
		SparseArray<std::reference_wrapper<Nz::UploadPool::Allocation>> _allocations;
	};
}
#endif //CONCERTO_NAZARARENDERER_HPP
