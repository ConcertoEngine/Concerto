//
// Created by arthur on 01/08/2022.
//

#include <filesystem>

#include "NazaraRenderer.hpp"
#include "Logger.hpp"


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

	NazaraRenderer::NazaraRenderer(const Config::Object& data) : ASystem(data),
																 _assetPath(data["assetPath"].as<std::string>()),
																 _nazara(nullptr),
																 _window(),
																 _camAngles(0.f, 0.f, 0.f),
																 _camQuat(_camAngles)
	{
		if (!std::filesystem::is_directory(_assetPath))
			Logger::error(_assetPath + " is not a valid directory");

		if (data["RenderingAPI"].as<Config::String>() == "Vulkan")
			_rendererConfig.preferredAPI = Nz::RenderAPI::Vulkan;
		else _rendererConfig.preferredAPI = Nz::RenderAPI::OpenGL;
		_nazara = std::make_unique<Nz::Modules<Nz::Renderer>>(_rendererConfig);
		_device = Nz::Renderer::Instance()->InstanciateRenderDevice(0);
		if (!_window.Create(_device, Nz::VideoMode(1280, 720, 32), data["GameName"].as<Config::String>()))
			Logger::error("Failed to create window");
		_windowSize = _window.GetSize();
		nzsl::Ast::ModulePtr shaderModule = nzsl::Parse(std::string_view(shaderSource, sizeof(shaderSource)));
		if (!shaderModule)
			Logger::error("Failed to parse shader module");
		_states.optionValues[Nz::CRC32("red")] = false;
		_states.optimize = true;
		_fragVertShader = _device->InstantiateShaderModule(
				nzsl::ShaderStageType::Fragment | nzsl::ShaderStageType::Vertex, *shaderModule, _states);
		if (!_fragVertShader)
			Logger::error("Failed to instantiate shader");
		_ubo.projectionMatrix = Nz::Matrix4f::Perspective(Nz::DegreeAnglef(70.f), float(_windowSize.x) / _windowSize.y,
				0.1f, 1000.f);
		_ubo.viewMatrix = Nz::Matrix4f::Translate(Nz::Vector3f::Backward() * 1);
		_ubo.modelMatrix = Nz::Matrix4f::Translate(Nz::Vector3f::Forward() * 2);
		auto& uboBinding = _pipelineLayoutInfo.bindings.emplace_back();
		uboBinding.setIndex = 0;
		uboBinding.bindingIndex = 0;
		uboBinding.shaderStageFlags = nzsl::ShaderStageType::Vertex;
		uboBinding.type = Nz::ShaderBindingType::UniformBuffer;
		_basePipelineLayout = _device->InstantiateRenderPipelineLayout(_pipelineLayoutInfo);
		auto& textureBinding = _pipelineLayoutInfo.bindings.emplace_back();
		textureBinding.setIndex = 1;
		textureBinding.bindingIndex = 0;
		textureBinding.shaderStageFlags = nzsl::ShaderStageType::Fragment;
		textureBinding.type = Nz::ShaderBindingType::Texture;
		_renderPipelineLayout = _device->InstantiateRenderPipelineLayout(std::move(_pipelineLayoutInfo));
		_viewerShaderBinding = _basePipelineLayout->AllocateShaderBinding(0);
		_textureShaderBinding = _renderPipelineLayout->AllocateShaderBinding(1);
		_uniformBuffer = _device->InstantiateBuffer(Nz::BufferType::Uniform, sizeof(UniformBufferObject),
				Nz::BufferUsage::DeviceLocal | Nz::BufferUsage::Dynamic);
		_viewerShaderBinding->Update({
				{
						0,
						Nz::ShaderBinding::UniformBufferBinding{
								_uniformBuffer.get(), 0, sizeof(UniformBufferObject)
						}
				}
		});
		Nz::RenderPipelineInfo pipelineInfo;
		pipelineInfo.pipelineLayout = _renderPipelineLayout;
		pipelineInfo.faceCulling = true;
		pipelineInfo.depthBuffer = true;
		pipelineInfo.shaderModules.emplace_back(_fragVertShader);
		auto& pipelineVertexBuffer = pipelineInfo.vertexBuffers.emplace_back();
		pipelineVertexBuffer.binding = 0;
		pipelineVertexBuffer.declaration = Nz::VertexDeclaration::Get(Nz::VertexLayout::XYZ_Normal_UV);
		_pipeline = _device->InstantiateRenderPipeline(pipelineInfo);
		const std::shared_ptr<Nz::RenderDevice>& renderDevice = _window.GetRenderDevice();
		_commandPool = renderDevice->InstantiateCommandPool(Nz::QueueType::Graphics);
		viewerShaderBinding = _basePipelineLayout->AllocateShaderBinding(0);
		textureShaderBinding = _renderPipelineLayout->AllocateShaderBinding(1);
		_window.EnableEventPolling(true);
		Nz::Mouse::SetRelativeMouseMode(true);
	}

	void NazaraRenderer::update(float deltaTime, Concerto::Ecs::Registry& r)
	{
		updateEvents();
		Nz::RenderFrame frame = _window.AcquireFrame();
		_ubo.viewMatrix = Nz::Matrix4f::TransformInverse(viewerPos, _camAngles);

		if (!frame)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			return;
		}

		if (_uboUpdate)
		{
			auto& allocation = frame.GetUploadPool().Allocate(sizeof(UniformBufferObject));

			std::memcpy(allocation.mappedPtr, &_ubo, sizeof(UniformBufferObject));

			frame.Execute([&](Nz::CommandBufferBuilder& builder)
			{
				builder.BeginDebugRegion("UBO Update", Nz::Color::Yellow);
				{
					builder.PreTransferBarrier();
					builder.CopyBuffer(allocation, _uniformBuffer.get());
					builder.PostTransferBarrier();
				}
				builder.EndDebugRegion();
			}, Nz::QueueType::Transfer);

			_uboUpdate = false;
		}
		const Nz::RenderTarget* windowRT = _window.GetRenderTarget();
		frame.Execute([&](Nz::CommandBufferBuilder& builder)
		{
			Nz::Recti renderRect(0, 0, _window.GetSize().x, _window.GetSize().y);

			Nz::CommandBufferBuilder::ClearValues clearValues[2];
			clearValues[0].color = Nz::Color::Blue;
			clearValues[1].depth = 1.f;
			clearValues[1].stencil = 0;

			builder.BeginDebugRegion("Main window rendering", Nz::Color::Green);
			{
				builder.BeginRenderPass(windowRT->GetFramebuffer(frame.GetFramebufferIndex()),
						windowRT->GetRenderPass(), renderRect, { clearValues[0], clearValues[1] });
				{
					for (Entity::Id entity = 0; entity < r.getEntityCount(); ++entity)
					{
						auto& transform = r.getComponent<Math::Transform>(entity);
						auto& meshComp = r.getComponent<Mesh>(entity);
						Nz::Mesh& mesh = createMeshIfNotExist(meshComp, transform);
						Nz::Texture& texture = createTextureIfNotExist(meshComp);
						std::shared_ptr<Nz::StaticMesh> sm = std::static_pointer_cast<Nz::StaticMesh>(
								mesh.GetSubMesh(0));
						const std::shared_ptr<Nz::VertexBuffer>& meshVB = sm->GetVertexBuffer();
						const std::shared_ptr<const Nz::IndexBuffer>& meshIB = sm->GetIndexBuffer();
						auto& renderBufferIB = dynamic_cast<Nz::RenderBuffer&>(*meshVB->GetBuffer());
						auto& renderBufferVB = dynamic_cast<Nz::RenderBuffer&>(*meshVB->GetBuffer());
						builder.BindIndexBuffer(renderBufferIB, Nz::IndexType::U16);
						builder.BindPipeline(*_pipeline);
						builder.BindVertexBuffer(0, renderBufferVB);
						builder.BindShaderBinding(0, *viewerShaderBinding);
						builder.BindShaderBinding(1, *textureShaderBinding);

						builder.SetScissor(Nz::Recti{ 0, 0, int(_windowSize.x), int(_windowSize.y) });
						builder.SetViewport(Nz::Recti{ 0, 0, int(_windowSize.x), int(_windowSize.y) });

						builder.DrawIndexed(meshIB->GetIndexCount());
					}
				}
				builder.EndRenderPass();
			}
			builder.EndDebugRegion();
		}, Nz::QueueType::Graphics);
		frame.Present();
	}

	void NazaraRenderer::stepUpdate(float deltaTime, Concerto::Ecs::Registry& r)
	{

	}

	Nz::Mesh& NazaraRenderer::createMeshIfNotExist(const Mesh& mesh, const Math::Transform& transform)
	{
		std::filesystem::path resourceDir = _assetPath;
		Nz::MeshParams meshParams;
		meshParams.bufferFactory = Nz::GetRenderBufferFactory(_device);
		meshParams.center = true;
//		meshParams.matrix = Nz::Matrix4f::Rotate(
//				Nz::EulerAnglesf(transform.Rotation.X(), transform.Rotation.Y(), transform.Rotation.Z())) *
//							Nz::Matrix4f::Scale(
//									Nz::Vector3f(transform.Scale.X(), transform.Scale.Y(), transform.Scale.Z()));
		meshParams.matrix =
				Nz::Matrix4f::Rotate(Nz::EulerAnglesf(0.f, -90.f, 0.f)) * Nz::Matrix4f::Scale(Nz::Vector3f(0.002f));
		meshParams.vertexDeclaration = Nz::VertexDeclaration::Get(Nz::VertexLayout::XYZ_Normal_UV);
		auto meshesIt = _meshes.find((resourceDir / mesh.modelPath).string());
		if (meshesIt == _meshes.end())
		{
			auto path = resourceDir / mesh.modelPath;
			auto meshPtr = Nz::Mesh::LoadFromFile(resourceDir / mesh.modelPath, meshParams);
			if (!meshPtr)
			{
				Logger::error("Fail to load model");
			}
			meshesIt = _meshes.emplace((resourceDir / mesh.modelPath).string(), meshPtr).first;
			Logger::debug("Created new mesh " + mesh.modelPath);
		}
		return *meshesIt->second;
	}

	Nz::Texture& NazaraRenderer::createTextureIfNotExist(const Mesh& mesh)
	{
		std::filesystem::path resourceDir = _assetPath;
		auto textureName = (resourceDir / mesh.texturePath).string();
		auto textureIt = _textures.find(textureName);

		if (textureIt == _textures.end())
		{
			Nz::TextureParams texParams;
			texParams.renderDevice = _device;
			texParams.loadFormat = Nz::PixelFormat::RGBA8_SRGB;

			auto meshPtr = Nz::Texture::LoadFromFile(resourceDir / mesh.texturePath, texParams);
			if (!meshPtr)
			{
				Logger::error("Fail to load model");
			}
			textureIt = _textures.emplace(textureName, meshPtr).first;
			std::shared_ptr<Nz::TextureSampler> textureSampler = _device->InstantiateTextureSampler({});
			_textureShaderBinding->Update({
					{
							0,
							Nz::ShaderBinding::TextureBinding{
									textureIt->second.get(), textureSampler.get()
							}
					}
			});
			Logger::debug("Created new texture " + mesh.texturePath);
		}
		return *textureIt->second;
	}

	void NazaraRenderer::updateEvents()
	{
		Nz::WindowEvent event;
		while (_window.PollEvent(&event))
		{
			switch (event.type)
			{
			case Nz::WindowEventType::Quit:
				_window.Close();
				break;

			case Nz::WindowEventType::MouseMoved: // La souris a bougé
			{
				// Gestion de la caméra free-fly (Rotation)
				float sensitivity = 0.3f; // Sensibilité de la souris

				// On modifie l'angle de la caméra grâce au déplacement relatif sur X de la souris
				_camAngles.yaw = _camAngles.yaw - event.mouseMove.deltaX * sensitivity;
				_camAngles.yaw.Normalize();

				// Idem, mais pour éviter les problèmes de calcul de la matrice de vue, on restreint les angles
				_camAngles.pitch = Nz::Clamp(_camAngles.pitch - event.mouseMove.deltaY * sensitivity, -89.f, 89.f);

				_camQuat = _camAngles;

				_uboUpdate = true;
				break;
			}

			case Nz::WindowEventType::Resized:
			{
				Nz::Vector2ui windowSize = _window.GetSize();
				_ubo.projectionMatrix = Nz::Matrix4f::Perspective(Nz::DegreeAnglef(70.f), float(windowSize.x) / windowSize.y, 0.1f, 1000.f);
				_uboUpdate = true;
				break;
			}

			default:
				break;
			}
		}
		if (updateClock.GetMilliseconds() > 1000 / 60)
		{
			float cameraSpeed = 2.f * updateClock.GetSeconds();
			updateClock.Restart();

			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Up) || Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Z))
				viewerPos += _camQuat * Nz::Vector3f::Forward() * cameraSpeed;

			// Si la flèche du bas ou la touche S est pressée, on recule
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Down) || Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::S))
				viewerPos += _camQuat * Nz::Vector3f::Backward() * cameraSpeed;

			// Etc...
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Left) || Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Q))
				viewerPos += _camQuat * Nz::Vector3f::Left() * cameraSpeed;

			// Etc...
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::Right) || Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::D))
				viewerPos += _camQuat * Nz::Vector3f::Right() * cameraSpeed;

			// Majuscule pour monter, notez l'utilisation d'une direction globale (Non-affectée par la rotation)
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::LShift) || Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::RShift))
				viewerPos += Nz::Vector3f::Up() * cameraSpeed;

			// Contrôle (Gauche ou droite) pour descendre dans l'espace global, etc...
			if (Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::LControl) || Nz::Keyboard::IsKeyPressed(Nz::Keyboard::VKey::RControl))
				viewerPos += Nz::Vector3f::Down() * cameraSpeed;

			_uboUpdate = true;
		}
	}
}
