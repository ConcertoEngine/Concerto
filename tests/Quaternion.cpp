//
// Created by arthur on 04/09/2022.
//

#include <gtest/gtest.h>

#include "Quaternion.hpp"

TEST(Quaternion, Quaternion)
{
	Concerto::Math::Quaternion<float> quaternion(1, 2, 3, 4);
	EXPECT_EQ(quaternion.X(), 1);
	EXPECT_EQ(quaternion.Y(), 2);
	EXPECT_EQ(quaternion.Z(), 3);
	EXPECT_EQ(quaternion.W(), 4);
}

TEST(Quaternion, operatorAdd)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion3 = quaternion1 + quaternion2;
	EXPECT_EQ(quaternion3.X(), 2);
	EXPECT_EQ(quaternion3.Y(), 4);
	EXPECT_EQ(quaternion3.Z(), 6);
	EXPECT_EQ(quaternion3.W(), 8);
}

TEST(Quaternion, operatorSub)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion3 = quaternion1 - quaternion2;
	EXPECT_EQ(quaternion3.X(), 0);
	EXPECT_EQ(quaternion3.Y(), 0);
	EXPECT_EQ(quaternion3.Z(), 0);
	EXPECT_EQ(quaternion3.W(), 0);
}

TEST(Quaternion, operatorMul)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion3 = quaternion1 * quaternion2;
	EXPECT_EQ(quaternion3.X(), -28);
	EXPECT_EQ(quaternion3.Y(), 4);
	EXPECT_EQ(quaternion3.Z(), 6);
	EXPECT_EQ(quaternion3.W(), 8);
}

TEST(Quaternion, operatorDiv)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion3 = quaternion1 / quaternion2;
	EXPECT_EQ(quaternion3.X(), 1);
	EXPECT_EQ(quaternion3.Y(), 1);
	EXPECT_EQ(quaternion3.Z(), 1);
	EXPECT_EQ(quaternion3.W(), 1);
}

TEST(Quaternion, operatorAddEqual)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2(1, 2, 3, 4);
	quaternion1 += quaternion2;
	EXPECT_EQ(quaternion1.X(), 2);
	EXPECT_EQ(quaternion1.Y(), 4);
	EXPECT_EQ(quaternion1.Z(), 6);
	EXPECT_EQ(quaternion1.W(), 8);
}

TEST(Quaternion, operatorSubEqual)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2(1, 2, 3, 4);
	quaternion1 -= quaternion2;
	EXPECT_EQ(quaternion1.X(), 0);
	EXPECT_EQ(quaternion1.Y(), 0);
	EXPECT_EQ(quaternion1.Z(), 0);
	EXPECT_EQ(quaternion1.W(), 0);
}

TEST(Quaternion, operatorMulEqual)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2(1, 2, 3, 4);
	quaternion1 *= quaternion2;
	EXPECT_EQ(quaternion1.X(), -28);
	EXPECT_EQ(quaternion1.Y(), 4);
	EXPECT_EQ(quaternion1.Z(), 6);
	EXPECT_EQ(quaternion1.W(), 8);
}

TEST(Quaternion, operatorDivEqual)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2(1, 2, 3, 4);
	quaternion1 /= quaternion2;
	EXPECT_EQ(quaternion1.X(), 1);
	EXPECT_EQ(quaternion1.Y(), 1);
	EXPECT_EQ(quaternion1.Z(), 1);
	EXPECT_EQ(quaternion1.W(), 1);
}

TEST(Quaternion, operatorEqual)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2(1, 2, 3, 4);
	EXPECT_EQ(quaternion1, quaternion2);
}

TEST(Quaternion, operatorNotEqual)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2(1, 2, 3, 4);
	EXPECT_NE(quaternion1, quaternion2);
}

TEST(Quaternion, operatorAddScalar)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2 = quaternion1 + 1;
	EXPECT_EQ(quaternion2.X(), 2);
	EXPECT_EQ(quaternion2.Y(), 3);
	EXPECT_EQ(quaternion2.Z(), 4);
	EXPECT_EQ(quaternion2.W(), 5);
}

TEST(Quaternion, operatorSubScalar)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2 = quaternion1 - 1;
	EXPECT_EQ(quaternion2.X(), 0);
	EXPECT_EQ(quaternion2.Y(), 1);
	EXPECT_EQ(quaternion2.Z(), 2);
	EXPECT_EQ(quaternion2.W(), 3);
}

TEST(Quaternion, operatorMulScalar)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2 = quaternion1 * 2;
	EXPECT_EQ(quaternion2.X(), 2);
	EXPECT_EQ(quaternion2.Y(), 4);
	EXPECT_EQ(quaternion2.Z(), 6);
	EXPECT_EQ(quaternion2.W(), 8);
}

TEST(Quaternion, operatorDivScalar)
{
	Concerto::Math::Quaternion<float> quaternion1(1, 2, 3, 4);
	Concerto::Math::Quaternion<float> quaternion2 = quaternion1 / 2;
	EXPECT_EQ(quaternion2.X(), 0.5);
	EXPECT_EQ(quaternion2.Y(), 1);
	EXPECT_EQ(quaternion2.Z(), 1.5);
	EXPECT_EQ(quaternion2.W(), 2);
}
