#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>

#include <Concerto/Core/StructuredData.hpp>
#include <Concerto/Core/Math/Transform.hpp>
#include <Concerto/Core/Math/Matrix.hpp>
#include <Concerto/Core/Math/Quaternion.hpp>
#include <Concerto/Graphics/Mesh.hpp>
#include <Concerto/Graphics/Camera.hpp>
#include <Concerto/Graphics/Window/Key.hpp>

#include "Registry.hpp"
#include "Ecs/World.hpp"
#include "Ecs/Systems/Renderer.hpp"

using namespace Concerto::Ecs;
using namespace Concerto;
using namespace Concerto::Math;

int main(int argc, const char** argv)
{
	try
	{
		std::ifstream file("./config.json");
		StructuredData structuredData(file);
		const Config::Object& config = structuredData.GetConfig();
		World world;
		Registry& r = world.GetRegistry();
		Graphics::RendererInfo info = {
			.applicationName = "Concerto Graphics",
			.applicationVersion = { 1, 0, 0 },
			.useImGUI = false,
			.width = 1280,
			.height = 720
		};
		auto& renderer = world.AddSystem<Ecs::System::Renderer>(std::move(info), config);

		auto entity = r.CreateEntity();
		Math::Transform transform(Vector3f(0.f, 0.f, 0.f), Quaternionf(EulerAnglesf(0.f, 0.f, 0.f)), Vector3f(1.f, 1.f, 1.f));
		r.EmplaceComponent<Math::Transform>(entity, transform);
		Graphics::MeshPtr mesh = std::make_shared<Graphics::Mesh>();
		mesh->LoadFromFile("./assets/sponza/sponza.obj");
		r.EmplaceComponent<Graphics::MeshPtr>(entity, mesh);

		auto cameraEntity = r.CreateEntity();
		Graphics::Camera camera(90.f, 0.1f, 1000000.f, 1280.f / 720.f);
		auto& cameraComp = r.EmplaceComponent<Graphics::Camera>(cameraEntity, std::move(camera));

		float cameraSpeed = 150.f;

		Input::Instance().Register("MouseMoved", MouseEvent::Type::Moved, [&](const MouseEvent& e, float deltaTime)
		{
		  cameraComp.Rotate(e.mouseMove.deltaX, -e.mouseMove.deltaY);
		});

		Input::Instance().Register("Forward", Key::Z, TriggerType::Held, [&](float deltaTime)
		{
		  cameraComp.Move(Concerto::Graphics::FreeFlyCameraMovement::Forward, deltaTime * cameraSpeed);
		});

		Input::Instance().Register("Backward", Key::S, TriggerType::Held, [&](float deltaTime)
		{
		  cameraComp.Move(Concerto::Graphics::FreeFlyCameraMovement::Backward, deltaTime * cameraSpeed);
		});

		Input::Instance().Register("Left", Key::Q, TriggerType::Held, [&](float deltaTime)
		{
		  cameraComp.Move(Concerto::Graphics::FreeFlyCameraMovement::Left, deltaTime * cameraSpeed);
		});

		Input::Instance().Register("Right", Key::D, TriggerType::Held, [&](float deltaTime)
		{
		  cameraComp.Move(Concerto::Graphics::FreeFlyCameraMovement::Right, deltaTime * cameraSpeed);
		});

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
