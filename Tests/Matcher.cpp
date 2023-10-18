//
// Created by arthur on 26/12/2022.
//

#include "Concerto/Ecs/Matcher.hpp"
#include <gtest/gtest.h>

using namespace Concerto;

struct Component1
{
	int a;
};
struct Component2
{
	int a;
};
struct Component3
{
	int a;
};
Component1 c1{1};
Component2 c2{2};
Component3 c3{2};
TEST(Matcher, TestAllOfCriteria)
{
	Registry r;
	Matcher m(r);
	m.AllOf<Component1, Component2>();
	Entity::Id entity1 = r.CreateEntity();
	Entity::Id entity2 = r.CreateEntity();
	Entity::Id entity3 = r.CreateEntity();
	r.EmplaceComponent<Component1>(entity1, c1);
	r.EmplaceComponent<Component2>(entity1, c2);
	r.EmplaceComponent<Component2>(entity2, c2);
	r.EmplaceComponent<Component3>(entity2, c3);
	r.EmplaceComponent<Component1>(entity3, c1);
	r.EmplaceComponent<Component3>(entity3, c3);
	EXPECT_TRUE(m.Matches(entity1));
	EXPECT_FALSE(m.Matches(entity2));
	EXPECT_FALSE(m.Matches(entity3));
}

TEST(Matcher, TestNoneOfCriteria)
{
	Registry r;
	Matcher m(r);
	Entity::Id entity1 = r.CreateEntity();
	Entity::Id entity2 = r.CreateEntity();
	Entity::Id entity3 = r.CreateEntity();
	r.EmplaceComponent<Component1>(entity1, c1);
	r.EmplaceComponent<Component2>(entity1, c2);
	r.EmplaceComponent<Component2>(entity2, c2);
	r.EmplaceComponent<Component3>(entity2, c3);
	r.EmplaceComponent<Component3>(entity3, c3);

	m.NoneOf<Component1, Component2>();
	EXPECT_FALSE(m.Matches(entity1));
	EXPECT_FALSE(m.Matches(entity2));
	EXPECT_TRUE(m.Matches(entity3));
}

TEST(Matcher, TestExcludeOfCriteria)
{
	Registry r;
	Matcher m(r);
	Entity::Id entity1 = r.CreateEntity();
	Entity::Id entity2 = r.CreateEntity();
	Entity::Id entity3 = r.CreateEntity();

	m.Exclude(entity1, entity2);
	EXPECT_FALSE(m.Matches(entity1));
	EXPECT_FALSE(m.Matches(entity2));
	EXPECT_TRUE(m.Matches(entity3));
}

TEST(Matcher, TestOnlyOfCriteria)
{
	Registry r;
	Matcher m(r);
	Entity::Id entity1 = r.CreateEntity();
	Entity::Id entity2 = r.CreateEntity();
	Entity::Id entity3 = r.CreateEntity();

	m.Only(entity1, entity2);
	EXPECT_TRUE(m.Matches(entity1));
	EXPECT_TRUE(m.Matches(entity2));
	EXPECT_FALSE(m.Matches(entity3));
}