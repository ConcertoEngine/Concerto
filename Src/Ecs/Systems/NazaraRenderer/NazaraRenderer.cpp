//
// Created by arthur on 01/08/2022.
//
#define NAZARA_DEBUG

#include <filesystem>

#include "NazaraRenderer.hpp"
#include "Concerto/Core/Logger.hpp"
#include "Input.hpp"

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
		  _app(),
		  _device(Nz::Graphics::Instance()->GetRenderDevice()),
		  _windowing(_app.AddComponent<Nz::AppWindowingComponent>()),
		  _window(_windowing.CreateWindow(Nz::VideoMode(1280, 720), "Concerto")),
		  _windowSwapchain(_device, _window)
	{

	}

	void NazaraRenderer::Update(float deltaTime, Concerto::Ecs::Registry& r)
	{

	}

	void NazaraRenderer::StepUpdate(float deltaTime, Concerto::Ecs::Registry& r)
	{

	}


	void NazaraRenderer::UpdateEvents(float deltaTime)
	{

	}

	bool NazaraRenderer::ShouldClose() const
	{
		return !_window.IsOpen();
	}
}
