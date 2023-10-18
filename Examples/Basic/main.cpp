#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

#include <Concerto/Core/StructuredData.hpp>
#include <Concerto/Core/Math/Transform.hpp>
#include <Concerto/Core/Math/Matrix.hpp>
#include <Concerto/Core/Math/Quaternion.hpp>

#include <Concerto/Ecs/Registry.hpp>
#include <Concerto/Ecs/World.hpp>
#include <Concerto/Ecs/Systems/Renderer.hpp>

#include <Nazara/Utility/SimpleTextDrawer.hpp>
#include <Nazara/Utility/Components/NodeComponent.hpp>

using namespace Concerto;
using namespace Concerto::Math;

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
		auto windowSize = Nz::Vector2f(renderer.GetWindow().GetSize());

		/*------------------------------------ Create entities ------------------------------------*/

		// Create a camera
		auto cameraEntity = r.CreateEntity();
		auto& camera = r.EmplaceComponent<Nz::Camera>(cameraEntity, &windowSwapchain);

		// create mesh

		auto meshEntity = r.CreateEntity();
		{
			Nz::Mesh sphereMesh;
			sphereMesh.CreateStatic();
			sphereMesh.BuildSubMesh(Nz::Primitive::UVSphere(1.f, 50, 50));
			sphereMesh.SetMaterialCount(1);
			sphereMesh.GenerateNormalsAndTangents();
			auto& gfxMesh = r.EmplaceComponent<std::shared_ptr<Nz::GraphicalMesh>>(meshEntity, Nz::GraphicalMesh::BuildFromMesh(sphereMesh));
			
			std::shared_ptr<Nz::MaterialInstance> materialInstance = Nz::MaterialInstance::Instantiate(Nz::MaterialType::PhysicallyBased);
			materialInstance->SetValueProperty("BaseColorMap", Nz::MaterialSettings::Value(Nz::Color(0, 255, 0)));
			auto& model = r.EmplaceComponent<Nz::Model>(meshEntity, gfxMesh);
			for (std::size_t i = 0; i < model.GetSubMeshCount(); ++i)
        model.SetMaterial(i, materialInstance);
		}

		// Create viewer instance

		auto viewerEntity = r.CreateEntity();
		Quaternionf rotation = EulerAnglesf(0.f, 0.f, 0.f).ToQuaternion();
		r.EmplaceComponent<Transform>(viewerEntity, Vector3f(0.f, 0.f, 0.f), rotation, Vector3f(1.f, 1.f, 1.f));
		Nz::ViewerInstance& viewerInstance = camera.GetViewerInstance();
		viewerInstance.UpdateTargetSize(windowSize);
		viewerInstance.UpdateProjViewMatrices(Nz::Matrix4f::Perspective(Nz::DegreeAnglef(70.f), float(windowSize.x) / windowSize.y, 0.1f, 1000.f), Nz::Matrix4f::Translate(Nz::Vector3f::Backward() * 1));

		// Create light
		//auto xx = std::make_any<Nz::DirectionalLight>();
		/*auto lightEntity = r.CreateEntity();
		auto& light = r.EmplaceComponent<Nz::DirectionalLight>(lightEntity, Nz::DirectionalLight());
		light.UpdateRotation(Nz::EulerAnglesf(-45.f, 0.f, 0.f));*/

		Nz::Mouse::SetRelativeMouseMode(true);

		/*------------------------------------ Game loop ------------------------------------*/
		float cameraSpeed = 150.f;

		std::chrono::steady_clock::time_point lastFrameTime = std::chrono::steady_clock::now();
		float deltaTime = 0.f;
		float timeStep = 0.02f;
		float timeUpdate = 0.016666f;
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