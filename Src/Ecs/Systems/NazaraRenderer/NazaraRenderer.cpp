//
// Created by arthur on 01/08/2022.
//
#define NAZARA_DEBUG

#include <filesystem>

#include "NazaraRenderer.hpp"
#include "Concerto/Core/Logger.hpp"
#include "Input.hpp"
#include "Matcher.hpp"
#include "components/Camera.hpp"

namespace Concerto::Ecs::System
{
	const char shaderSource[] = R"(
[nzsl_version("1.0")]
module;

option red: bool = false;

[layout(std140)]
struct Data
{
	projectionMatrix: mat4[f32],
	worldMatrix: mat4[f32],
	viewMatrix: mat4[f32]
}

[set(0)]
external
{
	[binding(0)] data: uniform[Data]
}

[set(1)]
external
{
	[binding(0)] tex: sampler2D[f32]
}

struct VertIn
{
	[location(0)] position: vec3[f32],
	[location(1)] normal: vec3[f32],
	[location(2)] uv: vec2[f32]
}

struct VertOut
{
	[builtin(position)] position: vec4[f32],
	[location(0)] normal: vec3[f32],
	[location(1)] uv: vec2[f32]
}

struct FragOut
{
	[location(0)] color: vec4[f32]
}

[entry(frag)]
fn main(fragIn: VertOut) -> FragOut
{
	let lightDir = vec3[f32](0.0, 0.707, 0.707);
	let lightFactor = dot(fragIn.normal, lightDir);

	let fragOut: FragOut;
	fragOut.color = lightFactor * tex.Sample(fragIn.uv) * const_select(red, vec4[f32](1.0, 0.0, 0.0, 1.0), vec4[f32](1.0, 1.0, 1.0, 1.0));

	return fragOut;
}

[entry(vert)]
fn main(vertIn: VertIn) -> VertOut
{
	let vertOut: VertOut;
	vertOut.position = data.projectionMatrix * data.viewMatrix * data.worldMatrix * vec4[f32](vertIn.position, 1.0);
	vertOut.normal = vertIn.normal;
	vertOut.uv = vertIn.uv;

	return vertOut;
}
)";

	NazaraRenderer::NazaraRenderer(const Config::Object& data)
		: System(data),
		  _assetsPath(data["assetPath"].AsString()),
		  _app(),
		  _device(Nz::Graphics::Instance()->GetRenderDevice()),
		  _windowing(_app.AddComponent<Nz::AppWindowingComponent>()),
		  _window(_windowing.CreateWindow(Nz::VideoMode(1280, 720), "Concerto")),
		  _windowSwapchain(_device, _window),
		  _camera(&_windowSwapchain),
		  _viewerInstance(_camera.GetViewerInstance()),
		  _modelInstance(std::make_shared<Nz::WorldInstance>()),
		  _windowScissorBox(Nz::Vector2i::Zero(), Nz::Vector2i(_window.GetSize())),
		  _elementRegistry(),
		  _framePipeline(_elementRegistry),
		  _cameraIndex(_framePipeline.RegisterViewer(&_camera, 0)),
		  _worldInstanceIndex(_framePipeline.RegisterWorldInstance(_modelInstance))
	{
		Nz::Vector2ui windowSize = _window.GetSize();
		_viewerInstance.UpdateTargetSize(Nz::Vector2f(_window.GetSize()));
		_viewerInstance.UpdateProjViewMatrices(Nz::Matrix4f::Perspective(
				Nz::DegreeAnglef(70.f), float(windowSize.x) / windowSize.y, 0.1f, 1000.f),
			Nz::Matrix4f::Translate(Nz::Vector3f::Backward() * 1));
		_modelInstance->UpdateWorldMatrix(Nz::Matrix4f::Translate(Nz::Vector3f::Forward() * 2 + Nz::Vector3f::Left()));
		_window.GetEventHandler().OnEvent.Connect([&](const Nz::WindowEventHandler*, const Nz::WindowEvent& event)
		{
			if (event.type == Nz::WindowEventType::Resized)
			{
				Nz::Vector2ui newWindowSize = _window.GetSize();
				_viewerInstance.UpdateProjectionMatrix(Nz::Matrix4f::Perspective(Nz::DegreeAnglef(70.f), float(newWindowSize.x) / newWindowSize.y, 0.1f, 1000.f));
				_viewerInstance.UpdateTargetSize(Nz::Vector2f(newWindowSize));
				_windowScissorBox = Nz::Recti(Nz::Vector2i::Zero(), Nz::Vector2i(newWindowSize));
			}
		});

	}

	void NazaraRenderer::Update(float deltaTime, Concerto::Ecs::Registry& r)
	{
		Nz::RenderFrame frame = _windowSwapchain.AcquireFrame();
		if (!frame)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			return;
		}
		Ecs::Matcher matcher(r);
		matcher.AllOf<Math::Transform, Mesh>();

		for (std::size_t entity = 0; entity < r.GetEntityCount(); ++entity)
		{
			if (!matcher.Matches(entity))
				continue;
			auto& transform = r.GetComponent<Math::Transform>(entity);
			auto& mesh = r.GetComponent<Mesh>(entity);
			auto& graphicalObject = CreateMeshIfNotExist(mesh.modelPath);

		}

		_framePipeline.Render(frame);

		frame.Present();
	}

	void NazaraRenderer::StepUpdate(float deltaTime, Concerto::Ecs::Registry& r)
	{

	}

	bool NazaraRenderer::ShouldClose() const
	{
		return !_window.IsOpen();
	}

	GraphicalObject& NazaraRenderer::CreateMeshIfNotExist(const std::string& path)
	{
		auto it = _meshes.find(path);
		if (it != _meshes.end())
			return it->second;
		std::shared_ptr<Nz::Mesh> mesh = Nz::Mesh::LoadFromFile(_assetsPath / path);
		GraphicalObject obj
			{
				.model = Nz::Model(Nz::GraphicalMesh::BuildFromMesh(*mesh), mesh->GetAABB()),
				.mesh = mesh,
				.materialInstance = CreateMaterialIfNotExist(path)
			};
		_framePipeline.RegisterRenderable(_worldInstanceIndex,
			Nz::FramePipeline::NoSkeletonInstance,
			&obj.model,
			0xFFFFFFFF,
			_windowScissorBox);
		for (std::size_t i = 0; i < obj.model.GetMaterialCount(); ++i)
			obj.model.SetMaterial(i, obj.materialInstance);
		auto newElement = _meshes.emplace(path, std::move(obj));
		return newElement.first->second;
	}

	std::shared_ptr<Nz::Texture> NazaraRenderer::CreateTextureIfNotExist(const std::string& path)
	{
		auto it = _textures.find(path);
		if (it != _textures.end())
			return it->second;
		Nz::TextureParams texParams;
		texParams.renderDevice = _device;
		std::shared_ptr<Nz::Texture> texture = Nz::Texture::LoadFromFile(_assetsPath / path, texParams);
		_textures.emplace(path, texture);
		return texture;
	}

	std::shared_ptr<Nz::MaterialInstance> NazaraRenderer::CreateMaterialIfNotExist(const std::string& path)
	{
		std::shared_ptr<Nz::Material> material = Nz::Graphics::Instance()->GetDefaultMaterials().pbrMaterial;
		Nz::TextureParams texParams;
		texParams.renderDevice = _device;
		std::shared_ptr<Nz::MaterialInstance> materialInstance = std::make_shared<Nz::MaterialInstance>(material);
		materialInstance->SetTextureProperty("BaseColorMap", CreateTextureIfNotExist(path));
		return materialInstance;
	}
}
