//
// Created by arthur on 16/06/2022.
//
#define CATCH_CONFIG_RUNNER

#include <iostream>
#include <catch2/catch.hpp>
#include "Registry.hpp"
#include "Transform.hpp"
#include "Vector.hpp"

using namespace Concerto::Ecs;
using namespace Concerto::Math;
using namespace Concerto;

TEST_CASE("Registry", "AddEntity")
{
	Registry r;
	Entity::Id entity = r.createEntity();
	REQUIRE(0 == entity);
	entity = r.createEntity();
	REQUIRE(1 == entity);
}

TEST_CASE("Registry", "addComponent")
{
	Registry r;
	Entity::Id entity = r.createEntity();
	auto &comp = r.emplaceComponent<Transform>(entity, Transform(Vector3f(0.f, 0.f, 0.f),  Vector3f(0.f, 0.f, 0.f), Vector3f(0.f, 0.f, 0.f)));
	auto &comp2 = r.getComponent<Transform>(entity);
	REQUIRE(&comp == &comp2);
}