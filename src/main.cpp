#include <cstdint>
#include <iostream>
#include <string>
#include "Registry.hpp"
#include "Entity.hpp"
#include "Transform.hpp"
#include "NazaraRenderer.hpp"
#include "ecs/World.hpp"
#include "StructuredData.hpp"
#include "Input.hpp"
#include "Matrix.hpp"
#include "Quaternion.hpp"
#include "Camera.hpp"
#include <algorithm>

using namespace Concerto::Ecs;
using namespace Concerto;
using namespace Concerto::Math;

int main()
{
	try
	{
		Input i;
		StructuredData structuredData("./config.json");
		const Config::Object& config = structuredData.getConfig();
		World world;
		Registry& r = world.GetRegistry();
		auto& renderer = world.AddSystem<System::NazaraRenderer>(config);


		{
			auto meshEntity = r.CreateEntity();
			Transform transform(Vector3f(0.f, 0.f, 0.f), Quaternionf(0.f, 0.f, 0.f, 0.f), Vector3f(0.f, 0.f, 0.f));
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

		Input::Instance().Register("MouseMove", MouseEvent::Type::Moved, [&](const MouseEvent& e)
		{
			float sensitivity = 0.3f; // Mouse sensitivity
			cameraComp.EulerAngles.X() = std::clamp(cameraComp.EulerAngles.X() - e.mouseMove.deltaY * sensitivity,
					-89.f, 89.f);
			cameraComp.EulerAngles.Y() = cameraComp.EulerAngles.Y() - e.mouseMove.deltaX * sensitivity;
		});
		Input::Instance().Register("Forward", Key::Z, TriggerType::Pressed, [&]()
		{
			Quaternionf q;
			q.Set(cameraComp.EulerAngles.X(), cameraComp.EulerAngles.Y(), cameraComp.EulerAngles.Z());

			cameraComp.Position += q * Vector3f::Forward() * 1 / 60;
		});
		Input::Instance().Register("Backward", Key::S, TriggerType::Pressed, [&]()
		{
			Quaternionf q;
			q.Set(cameraComp.EulerAngles.X(), cameraComp.EulerAngles.Y(), cameraComp.EulerAngles.Z());
			cameraComp.Position += q * Vector3f::Backward() * 1 / 60;
		});
		Input::Instance().Register("Left", Key::Q, TriggerType::Pressed, [&]()
		{
			Quaternionf q;
			q.Set(cameraComp.EulerAngles.X(), cameraComp.EulerAngles.Y(), cameraComp.EulerAngles.Z());
			cameraComp.Position += q * Vector3f::Left() * 1 / 60;
		});
		Input::Instance().Register("Right", Key::D, TriggerType::Pressed, [&]()
		{
			Quaternionf q;
			q.Set(cameraComp.EulerAngles.X(), cameraComp.EulerAngles.Y(), cameraComp.EulerAngles.Z());
			cameraComp.Position += q * Vector3f::Right() * 1 / 60;
		});

		while (!renderer.ShouldClose())
		{
//			try
//			{
				world.Update(1.f / 60.f);
//			}
//			catch (const std::exception& e)
//			{
//				std::cout << e.what() << std::endl;
//			}
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
