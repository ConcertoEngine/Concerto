//
// Created by arthur on 18/10/2023.
//

#include <memory>
#include <cstring>

#include <gtest/gtest.h>

#include <Concerto/Ecs/ErasedType.hpp>

using namespace Concerto;

TEST(ErasedType, Construction)
{
	//ErasedTypeImpl<int> intErased(6);
	//ErasedType &e = intErased;
	//int& value = e.As<int&>();
	//EXPECT_EQ(value, 6);
}

TEST(ErasedType, MakeErasedTypeFunc)
{
	//ErasedType erasedType = MakeErasedType<int>(6);
	//const int& value = erasedType.As<const int&>();
	//EXPECT_EQ(value, 6);
	using Pointer = std::unique_ptr<char*, std::function<void(char**)>>;

	
	std::string string = "Hello this is a testing string";
	char* str = string.data();
	Pointer ptr(&str, [&](char** ptr)
	{
		std::memset(str, 'W', string.size());
	});
	
	ErasedType erasedType2 = MakeErasedType<Pointer>(std::move(ptr));
	auto& value2 = erasedType2.As<const Pointer&>();
	EXPECT_EQ(*value2, str);
}