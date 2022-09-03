//
// Created by arthur on 30/08/2022.
//

#include <gtest/gtest.h>

#include "Matrix.hpp"

using namespace Concerto::Math;

TEST(Matrix, Constructor)
{
	Matrix<float, 3, 3> m{};
	ASSERT_EQ(3, m.GetWidth());
	ASSERT_EQ(3, m.GetHeight());
}

TEST(Matrix, GetElement)
{
	Matrix<float, 3, 3> m(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	ASSERT_EQ(1.f, m.GetElement(0, 0));
	ASSERT_EQ(2.f, m.GetElement(0, 1));
	ASSERT_EQ(3.f, m.GetElement(0, 2));
	ASSERT_EQ(4.f, m.GetElement(1, 0));
	ASSERT_EQ(5.f, m.GetElement(1, 1));
	ASSERT_EQ(6.f, m.GetElement(1, 2));
	ASSERT_EQ(7.f, m.GetElement(2, 0));
	ASSERT_EQ(8.f, m.GetElement(2, 1));
	ASSERT_EQ(9.f, m.GetElement(2, 2));
}

TEST(Matrix, operaorAdd)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m2(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m3 = m1 + m2;
	ASSERT_EQ(2.f, m3.GetElement(0, 0));
	ASSERT_EQ(4.f, m3.GetElement(0, 1));
	ASSERT_EQ(6.f, m3.GetElement(0, 2));
	ASSERT_EQ(8.f, m3.GetElement(1, 0));
	ASSERT_EQ(10.f, m3.GetElement(1, 1));
	ASSERT_EQ(12.f, m3.GetElement(1, 2));
	ASSERT_EQ(14.f, m3.GetElement(2, 0));
	ASSERT_EQ(16.f, m3.GetElement(2, 1));
	ASSERT_EQ(18.f, m3.GetElement(2, 2));
}

TEST(Matrix, operatorSub)
{

	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m2(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m3 = m1 - m2;
	ASSERT_EQ(0.f, m3.GetElement(0, 0));
	ASSERT_EQ(0.f, m3.GetElement(0, 1));
	ASSERT_EQ(0.f, m3.GetElement(0, 2));
	ASSERT_EQ(0.f, m3.GetElement(1, 0));
	ASSERT_EQ(0.f, m3.GetElement(1, 1));
	ASSERT_EQ(0.f, m3.GetElement(1, 2));
	ASSERT_EQ(0.f, m3.GetElement(2, 0));
	ASSERT_EQ(0.f, m3.GetElement(2, 1));
	ASSERT_EQ(0.f, m3.GetElement(2, 2));
}

TEST(Matrix, operatorMult)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m2(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m3 = m1 * m2;
	ASSERT_EQ(30.f, m3.GetElement(0, 0));
	ASSERT_EQ(36.f, m3.GetElement(0, 1));
	ASSERT_EQ(42.f, m3.GetElement(0, 2));
	ASSERT_EQ(66.f, m3.GetElement(1, 0));
	ASSERT_EQ(81.f, m3.GetElement(1, 1));
	ASSERT_EQ(96.f, m3.GetElement(1, 2));
	ASSERT_EQ(102.f, m3.GetElement(2, 0));
	ASSERT_EQ(126.f, m3.GetElement(2, 1));
	ASSERT_EQ(150.f, m3.GetElement(2, 2));
}

TEST(Matrix, operatorDiv)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m2(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m3 = m1 / m2;
	ASSERT_EQ(1.f, m3.GetElement(0, 0));
	ASSERT_EQ(1.f, m3.GetElement(0, 1));
	ASSERT_EQ(1.f, m3.GetElement(0, 2));
	ASSERT_EQ(1.f, m3.GetElement(1, 0));
	ASSERT_EQ(1.f, m3.GetElement(1, 1));
	ASSERT_EQ(1.f, m3.GetElement(1, 2));
	ASSERT_EQ(1.f, m3.GetElement(2, 0));
	ASSERT_EQ(1.f, m3.GetElement(2, 1));
	ASSERT_EQ(1.f, m3.GetElement(2, 2));
}

TEST(Matrix, operatorAddScalar)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m2 = m1 + 1.f;
	ASSERT_EQ(2.f, m2.GetElement(0, 0));
	ASSERT_EQ(3.f, m2.GetElement(0, 1));
	ASSERT_EQ(4.f, m2.GetElement(0, 2));
	ASSERT_EQ(5.f, m2.GetElement(1, 0));
	ASSERT_EQ(6.f, m2.GetElement(1, 1));
	ASSERT_EQ(7.f, m2.GetElement(1, 2));
	ASSERT_EQ(8.f, m2.GetElement(2, 0));
	ASSERT_EQ(9.f, m2.GetElement(2, 1));
	ASSERT_EQ(10.f, m2.GetElement(2, 2));
}

TEST(Matrix, operatorSubScalar)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m2 = m1 - 1.f;
	ASSERT_EQ(0.f, m2.GetElement(0, 0));
	ASSERT_EQ(1.f, m2.GetElement(0, 1));
	ASSERT_EQ(2.f, m2.GetElement(0, 2));
	ASSERT_EQ(3.f, m2.GetElement(1, 0));
	ASSERT_EQ(4.f, m2.GetElement(1, 1));
	ASSERT_EQ(5.f, m2.GetElement(1, 2));
	ASSERT_EQ(6.f, m2.GetElement(2, 0));
	ASSERT_EQ(7.f, m2.GetElement(2, 1));
	ASSERT_EQ(8.f, m2.GetElement(2, 2));
}


TEST(Matrix, operatorMultScalar)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m2 = m1 * 2.f;
	ASSERT_EQ(2.f, m2.GetElement(0, 0));
	ASSERT_EQ(4.f, m2.GetElement(0, 1));
	ASSERT_EQ(6.f, m2.GetElement(0, 2));
	ASSERT_EQ(8.f, m2.GetElement(1, 0));
	ASSERT_EQ(10.f, m2.GetElement(1, 1));
	ASSERT_EQ(12.f, m2.GetElement(1, 2));
	ASSERT_EQ(14.f, m2.GetElement(2, 0));
	ASSERT_EQ(16.f, m2.GetElement(2, 1));
	ASSERT_EQ(18.f, m2.GetElement(2, 2));
}

TEST(Matrix, operatorDivScalar)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m2 = m1 / 2.f;
	ASSERT_EQ(0.5f, m2.GetElement(0, 0));
	ASSERT_EQ(1.f, m2.GetElement(0, 1));
	ASSERT_EQ(1.5f, m2.GetElement(0, 2));
	ASSERT_EQ(2.f, m2.GetElement(1, 0));
	ASSERT_EQ(2.5f, m2.GetElement(1, 1));
	ASSERT_EQ(3.f, m2.GetElement(1, 2));
	ASSERT_EQ(3.5f, m2.GetElement(2, 0));
	ASSERT_EQ(4.f, m2.GetElement(2, 1));
	ASSERT_EQ(4.5f, m2.GetElement(2, 2));
}

TEST(Matrix, operatorAddAssign)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m2(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	m1 += m2;
	ASSERT_EQ(2.f, m1.GetElement(0, 0));
	ASSERT_EQ(4.f, m1.GetElement(0, 1));
	ASSERT_EQ(6.f, m1.GetElement(0, 2));
	ASSERT_EQ(8.f, m1.GetElement(1, 0));
	ASSERT_EQ(10.f, m1.GetElement(1, 1));
	ASSERT_EQ(12.f, m1.GetElement(1, 2));
	ASSERT_EQ(14.f, m1.GetElement(2, 0));
	ASSERT_EQ(16.f, m1.GetElement(2, 1));
	ASSERT_EQ(18.f, m1.GetElement(2, 2));
}

TEST(Matrix, operatorSubAssign)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m2(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	m1 -= m2;
	ASSERT_EQ(0.f, m1.GetElement(0, 0));
	ASSERT_EQ(0.f, m1.GetElement(0, 1));
	ASSERT_EQ(0.f, m1.GetElement(0, 2));
	ASSERT_EQ(0.f, m1.GetElement(1, 0));
	ASSERT_EQ(0.f, m1.GetElement(1, 1));
	ASSERT_EQ(0.f, m1.GetElement(1, 2));
	ASSERT_EQ(0.f, m1.GetElement(2, 0));
	ASSERT_EQ(0.f, m1.GetElement(2, 1));
	ASSERT_EQ(0.f, m1.GetElement(2, 2));
}

TEST(Matrix, operatorMultAssign)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m2(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	m1 *= m2;
	ASSERT_EQ(1.f, m1.GetElement(0, 0));
	ASSERT_EQ(4.f, m1.GetElement(0, 1));
	ASSERT_EQ(9.f, m1.GetElement(0, 2));
	ASSERT_EQ(16.f, m1.GetElement(1, 0));
	ASSERT_EQ(25.f, m1.GetElement(1, 1));
	ASSERT_EQ(36.f, m1.GetElement(1, 2));
	ASSERT_EQ(49.f, m1.GetElement(2, 0));
	ASSERT_EQ(64.f, m1.GetElement(2, 1));
	ASSERT_EQ(81.f, m1.GetElement(2, 2));
}

TEST(Matrix, operatorDivAssign)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	Matrix<float, 3, 3> m2(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	m1 /= m2;
	ASSERT_EQ(1.f, m1.GetElement(0, 0));
	ASSERT_EQ(1.f, m1.GetElement(0, 1));
	ASSERT_EQ(1.f, m1.GetElement(0, 2));
	ASSERT_EQ(1.f, m1.GetElement(1, 0));
	ASSERT_EQ(1.f, m1.GetElement(1, 1));
	ASSERT_EQ(1.f, m1.GetElement(1, 2));
	ASSERT_EQ(1.f, m1.GetElement(2, 0));
	ASSERT_EQ(1.f, m1.GetElement(2, 1));
	ASSERT_EQ(1.f, m1.GetElement(2, 2));
}

TEST(Matrix, operatorAddAssignScalar)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	m1 += 1.f;
	ASSERT_EQ(2.f, m1.GetElement(0, 0));
	ASSERT_EQ(3.f, m1.GetElement(0, 1));
	ASSERT_EQ(4.f, m1.GetElement(0, 2));
	ASSERT_EQ(5.f, m1.GetElement(1, 0));
	ASSERT_EQ(6.f, m1.GetElement(1, 1));
	ASSERT_EQ(7.f, m1.GetElement(1, 2));
	ASSERT_EQ(8.f, m1.GetElement(2, 0));
	ASSERT_EQ(9.f, m1.GetElement(2, 1));
	ASSERT_EQ(10.f, m1.GetElement(2, 2));
}

TEST(Matrix, operatorSubAssignScalar)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	m1 -= 1.f;
	ASSERT_EQ(0.f, m1.GetElement(0, 0));
	ASSERT_EQ(1.f, m1.GetElement(0, 1));
	ASSERT_EQ(2.f, m1.GetElement(0, 2));
	ASSERT_EQ(3.f, m1.GetElement(1, 0));
	ASSERT_EQ(4.f, m1.GetElement(1, 1));
	ASSERT_EQ(5.f, m1.GetElement(1, 2));
	ASSERT_EQ(6.f, m1.GetElement(2, 0));
	ASSERT_EQ(7.f, m1.GetElement(2, 1));
	ASSERT_EQ(8.f, m1.GetElement(2, 2));
}

TEST(Matrix, operatorMultAssignScalar)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	m1 *= 2.f;
	ASSERT_EQ(2.f, m1.GetElement(0, 0));
	ASSERT_EQ(4.f, m1.GetElement(0, 1));
	ASSERT_EQ(6.f, m1.GetElement(0, 2));
	ASSERT_EQ(8.f, m1.GetElement(1, 0));
	ASSERT_EQ(10.f, m1.GetElement(1, 1));
	ASSERT_EQ(12.f, m1.GetElement(1, 2));
	ASSERT_EQ(14.f, m1.GetElement(2, 0));
	ASSERT_EQ(16.f, m1.GetElement(2, 1));
	ASSERT_EQ(18.f, m1.GetElement(2, 2));
}

TEST(Matrix, operatorDivAssignScalar)
{
	Matrix<float, 3, 3> m1(1.f, 2.f, 3.f,
			4.f, 5.f, 6.f,
			7.f, 8.f, 9.f);
	m1 /= 2.f;
	ASSERT_EQ(0.5f, m1.GetElement(0, 0));
	ASSERT_EQ(1.f, m1.GetElement(0, 1));
	ASSERT_EQ(1.5f, m1.GetElement(0, 2));
	ASSERT_EQ(2.f, m1.GetElement(1, 0));
	ASSERT_EQ(2.5f, m1.GetElement(1, 1));
	ASSERT_EQ(3.f, m1.GetElement(1, 2));
	ASSERT_EQ(3.5f, m1.GetElement(2, 0));
	ASSERT_EQ(4.f, m1.GetElement(2, 1));
	ASSERT_EQ(4.5f, m1.GetElement(2, 2));
}