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

using namespace Concerto::Ecs;
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
		auto& renderer = world.AddSystem<Ecs::System::Renderer>(config);
		auto& windowSwapchain = renderer.GetWindowSwapchain();
		
		auto cameraEntity = r.CreateEntity();
		{
			r.EmplaceComponent<Nz::NodeComponent>(cameraEntity);
			auto& cameraComponent = r.EmplaceComponent<Nz::CameraComponent>(cameraEntity, &windowSwapchain, Nz::ProjectionType::Orthographic);
			cameraComponent.UpdateClearColor(Nz::Color(0.46f, 0.48f, 0.84f, 1.f));
		}
		
		Nz::SimpleTextDrawer textDrawer;
		textDrawer.SetText("Hello world !");
		textDrawer.SetCharacterSize(72);
		textDrawer.SetTextOutlineThickness(4.f);
		
		std::shared_ptr<Nz::TextSprite> textSprite = std::make_shared<Nz::TextSprite>();
		textSprite->Update(textDrawer);

		auto textEntity = r.CreateEntity();
		{
			auto& nodeComponent = r.EmplaceComponent<Nz::NodeComponent>(textEntity);

			auto& gfxComponent = r.EmplaceComponent<Nz::GraphicsComponent>(textEntity);
			gfxComponent.AttachRenderable(textSprite);

			Nz::Boxf textBox = textSprite->GetAABB();
			Nz::Vector2ui windowSize = windowSwapchain.GetSize();
			nodeComponent.SetPosition(windowSize.x / 2 - textBox.width / 2, windowSize.y / 2 - textBox.height / 2);
		}

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
				textDrawer.SetCharacterSize(textDrawer.GetCharacterSize() + 1);
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