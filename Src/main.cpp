#include <iostream>
#include <algorithm>
#include <chrono>
#include "Registry.hpp"
#include "Entity.hpp"
#include "NazaraRenderer.hpp"
#include "ecs/World.hpp"
#include "Input.hpp"
#include "Concerto/Core/Logger.hpp"
#include "Concerto/Core/StructuredData.hpp"
#include "Concerto/Core/Math/Transform.hpp"
#include "Concerto/Core/Math/Matrix.hpp"
#include "Concerto/Core/Math/Quaternion.hpp"
#include "Camera.hpp"
#include "Observer.hpp"
#include "Matcher.hpp"

using namespace Concerto::Ecs;
using namespace Concerto;
using namespace Concerto::Math;

int main()
{
	try
	{
		Input input;
		StructuredData structuredData("./config.json");
		const Config::Object& config = structuredData.GetConfig();
		World world;
		Registry& r = world.GetRegistry();
		auto& renderer = world.AddSystem<System::NazaraRenderer>(config);


		for (Entity::Id entity = 0; entity < 100; ++entity)
		{
			auto meshEntity = r.CreateEntity();
			Transform transform(Vector3f(entity, 0.f, 0.f), Quaternionf(0.f, 0.f, 0.f, 0.f), Vector3f(1.f, 1.f, 1.f));
			auto& transformComp = r.EmplaceComponent<Transform>(meshEntity, transform);
			Mesh mesh;
			mesh.modelPath = "spaceship.obj";
			mesh.texturePath = "diffuse.png";
			auto& meshComp = r.EmplaceComponent<Mesh>(meshEntity, std::move(mesh));
		}

		auto cameraEntity = r.CreateEntity();
		Camera camera{};
		camera.Position = Vector3f(0.f, 0.f, 0.f);
		auto& cameraComp = r.EmplaceComponent<Camera>(cameraEntity, camera);
		float cameraSpeed = 10.f;
		Input::Instance().Register("MouseMove", MouseEvent::Type::Moved, [&](const MouseEvent& e, float deltaTime)
		{
			float sensitivity = 0.3f; // Mouse sensitivity
			cameraComp.EulerAngles.X() = std::clamp(cameraComp.EulerAngles.X() - e.mouseMove.deltaY * sensitivity,
					-89.f, 89.f);
			cameraComp.EulerAngles.Y() = cameraComp.EulerAngles.Y() - e.mouseMove.deltaX * sensitivity;
		});
		Input::Instance().Register("Forward", Key::Z, TriggerType::Pressed, [&](float deltaTime)
		{
			Quaternionf q;
			q.Set(cameraComp.EulerAngles.X(), cameraComp.EulerAngles.Y(), cameraComp.EulerAngles.Z());
			cameraComp.Position += q * Vector3f::Forward() * deltaTime * cameraSpeed;
		});
		Input::Instance().Register("Backward", Key::S, TriggerType::Pressed, [&](float deltaTime)
		{
			Quaternionf q;
			q.Set(cameraComp.EulerAngles.X(), cameraComp.EulerAngles.Y(), cameraComp.EulerAngles.Z());
			cameraComp.Position += q * Vector3f::Backward() * deltaTime * cameraSpeed;
		});
		Input::Instance().Register("Left", Key::Q, TriggerType::Pressed, [&](float deltaTime)
		{
			Quaternionf q;
			q.Set(cameraComp.EulerAngles.X(), cameraComp.EulerAngles.Y(), cameraComp.EulerAngles.Z());
			cameraComp.Position += q * Vector3f::Left() * deltaTime * cameraSpeed;
		});
		Input::Instance().Register("Right", Key::D, TriggerType::Pressed, [&](float deltaTime)
		{
			Quaternionf q;
			q.Set(cameraComp.EulerAngles.X(), cameraComp.EulerAngles.Y(), cameraComp.EulerAngles.Z());
			cameraComp.Position += q * Vector3f::Right() * deltaTime * cameraSpeed;
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
