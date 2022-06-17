//
// Created by arthur on 16/06/2022.
//

#include <gtest/gtest.h>
#include "Registry.hpp"
#include "Transform.hpp"
#include "Vector.hpp"

using namespace Concerto::Ecs;
using namespace Concerto::Math;
using namespace Concerto;

TEST(Registry, AddEntity)
{
	Registry r;
	Entity::Id entity = r.createEntity();
	ASSERT_EQ(0, entity);
	entity = r.createEntity();
	ASSERT_EQ(1, entity);
}

TEST(Registry, addComponent)
{
	Registry r;
	Entity::Id entity = r.createEntity();
	Transform transform(Vector3f(0.f, 0.f, 0.f),  Vector3f(0.f, 0.f, 0.f), Vector3f(0.f, 0.f, 0.f));
	auto &comp = r.emplaceComponent<Transform>(entity, transform);
	ASSERT_EQ(comp, transform);
}

TEST(Registry, getComponent)
{
	Registry r;
	Entity::Id entity = r.createEntity();
	Transform transform(Vector3f(0.f, 0.f, 0.f),  Vector3f(0.f, 0.f, 0.f), Vector3f(0.f, 0.f, 0.f));
	auto &comp = r.emplaceComponent<Transform>(entity, transform);
	auto &comp2 = r.getComponent<Transform>(entity);
	ASSERT_EQ(&comp, &comp2);
}

TEST(Registry, removeComponent)
{
	Registry r;
	Entity::Id entity = r.createEntity();
	Transform transform(Vector3f(0.f, 0.f, 0.f),  Vector3f(0.f, 0.f, 0.f), Vector3f(0.f, 0.f, 0.f));
	auto& comp = r.emplaceComponent<Transform>(entity, transform);
	r.removeComponent<Transform>(entity);
	try {
		auto& comp2 = r.getComponent<Transform>(entity);
		FAIL();
	}
	catch (const std::runtime_error &e) {
		SUCCEED();
	}
}

TEST(Registry, hasComponent)
{
	Registry r;
	Entity::Id entity = r.createEntity();
	Transform transform(Vector3f(0.f, 0.f, 0.f),  Vector3f(0.f, 0.f, 0.f), Vector3f(0.f, 0.f, 0.f));
	auto& comp = r.emplaceComponent<Transform>(entity, transform);
	ASSERT_TRUE(r.hasComponent<Transform>(entity));
	r.removeComponent<Transform>(entity);
	ASSERT_FALSE(r.hasComponent<Transform>(entity));
}