#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

#include <Concerto/Core/StructuredData.hpp>

#include <Concerto/Engine/Ecs/Registry.hpp>
#include <Concerto/Engine/Ecs/World.hpp>
#include <Concerto/Engine/Graphics/Renderer.hpp>

#include <Nazara/Renderer.hpp>

using namespace Concerto;

int main([[maybe_unused]] int argc, [[maybe_unused]] const char** argv)
{
	try
	{
		std::ifstream file("./config.json");
		StructuredData structuredData(file);
		const Config::Object& config = structuredData.GetConfig();
		World world;
		Registry& r = world.GetRegistry();

		auto& renderer = world.AddSystem<Renderer>(config);
		auto& windowSwapchain = renderer.GetWindowSwapchain();
		auto& window = renderer.GetWindow();

		auto renderWindow = std::make_shared<Nz::RenderWindow>(windowSwapchain);
		Nz::EulerAnglesf camAngles(0.f, 0.f, 0.f);
		Nz::Quaternionf camQuat(camAngles);
		Nz::Vector3f viewerPos = Nz::Vector3f::Zero();

		auto windowSize = Nz::Vector2f(windowSwapchain.GetSize());

		Nz::Camera camera(renderWindow);
		Nz::ViewerInstance& viewerInstance = camera.GetViewerInstance();
		viewerInstance.UpdateTargetSize(Nz::Vector2f(windowSwapchain.GetSize()));
		viewerInstance.UpdateProjViewMatrices(Nz::Matrix4f::Perspective(Nz::DegreeAnglef(70.f), windowSize.x / windowSize.y, 0.1f, 1000.f), Nz::Matrix4f::Translate(Nz::Vector3f::Backward() * 1));
		viewerInstance.UpdateNearFarPlanes(0.1f, 1000.f);
		renderer.SetViewerInstance(viewerInstance, camera);
		camera.UpdateClearColor(Nz::Color(0.46f, 0.48f, 0.84f, 1.f));

		
		Nz::TextureParams texParams;
		texParams.renderDevice = Nz::Graphics::Instance()->GetRenderDevice();

		Nz::TextureParams srgbTexParams = texParams;
		srgbTexParams.loadFormat = Nz::PixelFormat::RGBA8_SRGB;
		
		std::shared_ptr<Nz::MaterialInstance> materialInstance = Nz::MaterialInstance::Instantiate(Nz::MaterialType::PhysicallyBased);
		materialInstance->SetTextureProperty("BaseColorMap", Nz::Texture::LoadFromFile(config["AssetsPath"].AsString() + "/Concerto.png", srgbTexParams));

		std::shared_ptr<Nz::Mesh> sphereMesh = std::make_shared<Nz::Mesh>();
		sphereMesh->CreateStatic();
		sphereMesh->BuildSubMesh(Nz::Primitive::UVSphere(1.f, 50, 50));
		sphereMesh->SetMaterialCount(1);
		sphereMesh->GenerateNormalsAndTangents();

		std::shared_ptr<Nz::GraphicalMesh> gfxMesh = Nz::GraphicalMesh::BuildFromMesh(*sphereMesh);

		auto modelEntity = r.CreateEntity();
		{
			auto& model = r.EmplaceComponent<std::shared_ptr<Nz::Model>>(modelEntity, std::make_shared<Nz::Model>(std::move(gfxMesh)));
			for (std::size_t i = 0; i < model->GetSubMeshCount(); ++i)
				model->SetMaterial(i, materialInstance);
		}

		auto lightEntity = r.CreateEntity();
		{
			auto& light = r.EmplaceComponent<Nz::DirectionalLight>(lightEntity);
			light.UpdateRotation(Nz::EulerAnglesf(-45.f, 0.f, 0.f));
		}
		Nz::Mouse::SetRelativeMouseMode(true);
		window.GetEventHandler().OnEvent.Connect([&](const Nz::WindowEventHandler*, const Nz::WindowEvent& event)
		{
			switch (event.type)
			{
			case Nz::WindowEventType::MouseMoved:
			{
				const float sensitivity = 0.3f;

				camAngles.yaw = camAngles.yaw - event.mouseMove.deltaX * sensitivity;
				camAngles.yaw.Normalize();
				camAngles.pitch = Nz::Clamp(camAngles.pitch - event.mouseMove.deltaY * sensitivity, -89.f, 89.f);
				camQuat = camAngles;
				break;
			}

			case Nz::WindowEventType::Resized:
			{
				const Nz::Vector2ui newWindowSize = window.GetSize();
				viewerInstance.UpdateProjectionMatrix(Nz::Matrix4f::Perspective(Nz::DegreeAnglef(70.f), float(newWindowSize.x) / newWindowSize.y, 0.1f, 1000.f));
				viewerInstance.UpdateTargetSize(Nz::Vector2f(newWindowSize));
				break;
			}

			default:
				break;
			}
		});
		

		std::chrono::steady_clock::time_point lastFrameTime = std::chrono::steady_clock::now();
		float deltaTime = 0.f;
		constexpr float timeStep = 0.02f;
		constexpr float timeUpdate = 0.016666f;
		float stepUpdateRemainingTime = 0.f;
		float updateRemainingTime = 0.f;

		while (!renderer.ShouldClose())
		{
			auto beginTime = std::chrono::high_resolution_clock::now();
			deltaTime = std::chrono::duration<float>(beginTime - lastFrameTime).count();
			lastFrameTime = beginTime;
			stepUpdateRemainingTime += deltaTime;
			updateRemainingTime += deltaTime;

			while (updateRemainingTime >= timeUpdate)
			{
				world.Update(updateRemainingTime);
				viewerInstance.UpdateViewMatrix(Nz::Matrix4f::TransformInverse(viewerPos, camAngles));
				viewerInstance.UpdateEyePosition(viewerPos);
				updateRemainingTime -= timeUpdate;
			}

			while (stepUpdateRemainingTime >= timeStep)
			{
				world.StepUpdate(timeStep);
				stepUpdateRemainingTime -= timeStep;
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}