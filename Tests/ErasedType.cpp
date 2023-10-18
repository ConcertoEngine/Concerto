//
// Created by arthur on 18/10/2023.
//

#include <gtest/gtest.h>

#include <Concerto/Ecs/ErasedType.hpp>

using namespace Concerto;

TEST(ErasedType, Construction)
{
	//auto intErased = MakeErasedType(6);
	//auto& value = intErased.As<int&>();
	ErasedTypeImpl<int> intErased(6);
	ErasedType &e = intErased;
	int& value = e.As<int&>();
	EXPECT_EQ(value, 6);
}