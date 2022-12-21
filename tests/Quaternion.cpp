//
// Created by arthur on 04/09/2022.
//

#include <gtest/gtest.h>

#include "Quaternion.hpp"
constexpr float near = 0.001f;

TEST(Quaternion, Quaternion)
{
	Concerto::Math::Quaternionf quaternion(1, 2, 3, 4);
	EXPECT_EQ(quaternion.X(), 1);
	EXPECT_EQ(quaternion.Y(), 2);
	EXPECT_EQ(quaternion.Z(), 3);
	EXPECT_EQ(quaternion.W(), 4);
}

TEST(Quaternion, operatorAdd)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternionf quaternion2(1, 2, 3, 4);
	Concerto::Math::Quaternionf quaternion3 = quaternion1 + quaternion2;
	EXPECT_EQ(quaternion3.X(), 2);
	EXPECT_EQ(quaternion3.Y(), 4);
	EXPECT_EQ(quaternion3.Z(), 6);
	EXPECT_EQ(quaternion3.W(), 8);
}

TEST(Quaternion, operatorSub)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternionf quaternion2(1, 2, 3, 4);
	Concerto::Math::Quaternionf quaternion3 = quaternion1 - quaternion2;
	EXPECT_EQ(quaternion3.X(), 0);
	EXPECT_EQ(quaternion3.Y(), 0);
	EXPECT_EQ(quaternion3.Z(), 0);
	EXPECT_EQ(quaternion3.W(), 0);
}

TEST(Quaternion, operatorMul)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3);
	Concerto::Math::Quaternionf quaternion2(1, 2, 3);
	Concerto::Math::Quaternionf quaternion3 = quaternion1 * quaternion2;
	EXPECT_NEAR(quaternion3.X(), 0.0183483884f, near);
	EXPECT_NEAR(quaternion3.Y(), 0.0344165042, near);
	EXPECT_NEAR(quaternion3.Z(), 0.0520119108, near);
	EXPECT_NEAR(quaternion3.W(), 0.997884572, near);
}

TEST(Quaternion, operatorDiv)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3);
	Concerto::Math::Quaternionf quaternion2(1, 2, 3);
	Concerto::Math::Quaternionf quaternion3 = quaternion1 / quaternion2;
	EXPECT_NEAR(quaternion3.X(), -0.0183483884f, near);
	EXPECT_NEAR(quaternion3.Y(), -0.0344165042, near);
	EXPECT_NEAR(quaternion3.Z(), -0.0520119108, near);
	EXPECT_NEAR(quaternion3.W(), -0.997884572, near);
}

TEST(Quaternion, operatorAddEqual)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternionf quaternion2(1, 2, 3, 4);
	quaternion1 += quaternion2;
	EXPECT_EQ(quaternion1.X(), 2);
	EXPECT_EQ(quaternion1.Y(), 4);
	EXPECT_EQ(quaternion1.Z(), 6);
	EXPECT_EQ(quaternion1.W(), 8);
}

TEST(Quaternion, operatorSubEqual)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternionf quaternion2(1, 2, 3, 4);
	quaternion1 -= quaternion2;
	EXPECT_EQ(quaternion1.X(), 0);
	EXPECT_EQ(quaternion1.Y(), 0);
	EXPECT_EQ(quaternion1.Z(), 0);
	EXPECT_EQ(quaternion1.W(), 0);
}

TEST(Quaternion, operatorMulEqual)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3);
	Concerto::Math::Quaternionf quaternion2(1, 2, 3);
	quaternion1 *= quaternion2;
	EXPECT_NEAR(quaternion1.X(), 0.0183483884f, near);
	EXPECT_NEAR(quaternion1.Y(), 0.0344165042, near);
	EXPECT_NEAR(quaternion1.Z(), 0.0520119108, near);
	EXPECT_NEAR(quaternion1.W(), 0.997884572, near);
}

TEST(Quaternion, operatorDivEqual)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3);
	Concerto::Math::Quaternionf quaternion2(1, 2, 3);
	quaternion1 /= quaternion2;
	EXPECT_NEAR(quaternion1.X(), -0.0183483884f, near);
	EXPECT_NEAR(quaternion1.Y(), -0.0344165042, near);
	EXPECT_NEAR(quaternion1.Z(), -0.0520119108, near);
	EXPECT_NEAR(quaternion1.W(), -0.997884572, near);
}

TEST(Quaternion, operatorEqual)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternionf quaternion2(1, 2, 3, 4);
	EXPECT_EQ(quaternion1, quaternion2);
}

TEST(Quaternion, operatorNotEqual)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternionf quaternion2(1, 2, 3, 5);
	EXPECT_NE(quaternion1, quaternion2);
}

TEST(Quaternion, operatorAddScalar)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternionf quaternion2 = quaternion1 + 1;
	EXPECT_EQ(quaternion2.X(), 2);
	EXPECT_EQ(quaternion2.Y(), 3);
	EXPECT_EQ(quaternion2.Z(), 4);
	EXPECT_EQ(quaternion2.W(), 5);
}

TEST(Quaternion, operatorSubScalar)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternionf quaternion2 = quaternion1 - 1;
	EXPECT_EQ(quaternion2.X(), 0);
	EXPECT_EQ(quaternion2.Y(), 1);
	EXPECT_EQ(quaternion2.Z(), 2);
	EXPECT_EQ(quaternion2.W(), 3);
}

TEST(Quaternion, operatorMulScalar)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternionf quaternion2 = quaternion1 * 2;
	EXPECT_EQ(quaternion2.X(), 2);
	EXPECT_EQ(quaternion2.Y(), 4);
	EXPECT_EQ(quaternion2.Z(), 6);
	EXPECT_EQ(quaternion2.W(), 8);
}

TEST(Quaternion, operatorDivScalar)
{
	Concerto::Math::Quaternionf quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternionf quaternion2 = quaternion1 / 2;
	EXPECT_EQ(quaternion2.X(), 0.5);
	EXPECT_EQ(quaternion2.Y(), 1);
	EXPECT_EQ(quaternion2.Z(), 1.5);
	EXPECT_EQ(quaternion2.W(), 2);
}

TEST(Quaternion, operatorMultVector)
{
	Concerto::Math::Quaternionf quaternion1(1,2,3);
	Concerto::Math::Vector3f vec = quaternion1 * Concerto::Math::Vector3f::Forward();
	EXPECT_NEAR(vec.X(), 0.0348941758, near);
	EXPECT_NEAR(vec.Y(), -0.0174524058, near);
	EXPECT_NEAR(vec.Z(), 0.99923861, near);
}
