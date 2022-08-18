#include <cstdint>
#include <iostream>
#include <string>
#include "Registry.hpp"
#include "Entity.hpp"
#include "Transform.hpp"
#include "systems/NazaraRenderer.hpp"
#include "ecs/World.hpp"
#include "StructuredData.hpp"
#include "Input.hpp"

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

		auto entity = r.CreateEntity();
		Transform transform(Vector3f(0.f, 0.f, 0.f), Vector3f(0.f, 0.f, 0.f), Vector3f(0.f, 0.f, 0.f));
		auto& transformComp = r.EmplaceComponent<Transform>(entity, transform);
		Mesh mesh;
		mesh.modelPath = "spaceship.obj";
		mesh.texturePath = "diffuse.png";
		auto& meshComp = r.EmplaceComponent<Mesh>(entity, std::move(mesh));

		i.Register("forward", Key::Z, TriggerType::Pressed, []()
		{
			std::cout << "Key Z" << std::endl;
		});
		i.Register("forward", Key::Up, TriggerType::Pressed, []()
		{
			std::cout << "Key Up" << std::endl;
		});
		i.Register("mouse", MouseEvent::Type::Wheel, [](const MouseEvent& e)
		{
			std::cout << "x " << e.mouseWheel.x << std::endl;
			std::cout << "y " << e.mouseWheel.y << std::endl;

			std::cout << "delta " << e.mouseWheel.delta << std::endl;
		});
		while (!renderer.ShouldClose())
		{
			world.Update(1.f / 60.f);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
