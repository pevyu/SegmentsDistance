#include <gtest/gtest.h>

#include "Vector3D.h"

TEST(Vector3D, hasZeroLength){
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	
    Vector3D v1(p1, p1);
    Vector3D v2(p1, p2);
	
	ASSERT_DOUBLE_EQ(v1.x, 0.0);
	ASSERT_DOUBLE_EQ(v1.y, 0.0);
	ASSERT_DOUBLE_EQ(v1.z, 0.0);
	ASSERT_TRUE(v1.hasZeroLength);
	
	ASSERT_DOUBLE_EQ(v2.x, 1.0);
	ASSERT_DOUBLE_EQ(v2.y, 1.0);
	ASSERT_DOUBLE_EQ(v2.z, 1.0);
	ASSERT_FALSE(v2.hasZeroLength);
}

TEST(Vector3D, Length) {
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);

	Vector3D v1(p1, p2);
	Vector3D v2(p2, p1);

	ASSERT_DOUBLE_EQ(v1.length(), std::sqrt(3.0));
	ASSERT_DOUBLE_EQ(v2.length(), std::sqrt(3.0));
	ASSERT_DOUBLE_EQ((v1 - v2).length(), 2 * std::sqrt(3.0));
	ASSERT_DOUBLE_EQ((v2 - v1).length(), 2 * std::sqrt(3.0));

	Vector3D v4(Point3D(3000, 0, 0), Point3D(3000, 4000, 0));
	Vector3D v5(p1, Point3D(3000, 4000, 0));
	Vector3D v3 = v5 - v4;		// Calculate the smaller side of 2D-Egyptian triangle
	ASSERT_DOUBLE_EQ(v3.length(), 3000.0);
	Vector3D v6 = v1 - v1;
	ASSERT_DOUBLE_EQ(v6.length(), 0.0);
}

TEST(Vector3D, OperatorPlus){
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	
	Vector3D v1(p1, p2);
	Vector3D v2(p2, p1);
	
	ASSERT_DOUBLE_EQ((v1 + v2).x, 0.0);
	ASSERT_DOUBLE_EQ((v1 + v2).y, 0.0);
	ASSERT_DOUBLE_EQ((v1 + v2).z, 0.0);
	ASSERT_DOUBLE_EQ((v1 + v2).length(), 0.0);
	ASSERT_DOUBLE_EQ((v2 + v1).x, 0.0);
	ASSERT_DOUBLE_EQ((v2 + v1).y, 0.0);
	ASSERT_DOUBLE_EQ((v2 + v1).z, 0.0);
	ASSERT_DOUBLE_EQ((v2 + v1).length(), 0.0);
	
	Vector3D v3(p1, Point3D(3,0,0));
	Vector3D v4(Point3D(3,0,0), Point3D(3,4,0));
	Vector3D v5 = v3 + v4;		// 2D-Egyptian triangle
	ASSERT_DOUBLE_EQ(v5.x, 3.0);
	ASSERT_DOUBLE_EQ(v5.y, 4.0);
	ASSERT_DOUBLE_EQ(v5.z, 0.0);
	ASSERT_DOUBLE_EQ(v5.length(), 5.0);
    Vector3D v6 = v1 + v1;
	ASSERT_DOUBLE_EQ(v6.x, 2.0);
	ASSERT_DOUBLE_EQ(v6.y, 2.0);
	ASSERT_DOUBLE_EQ(v6.z, 2.0);
}

TEST(Vector3D, OperatorMinus) {
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);

	Vector3D v1(p1, p2);
	Vector3D v2(p2, p1);

	ASSERT_DOUBLE_EQ((v1 - v2).x, 2.0);
	ASSERT_DOUBLE_EQ((v1 - v2).y, 2.0);
	ASSERT_DOUBLE_EQ((v1 - v2).z, 2.0);
	ASSERT_DOUBLE_EQ((v1 - v2).length(), 2 * std::sqrt(3.0));
	ASSERT_DOUBLE_EQ((v2 - v1).x, -2.0);
	ASSERT_DOUBLE_EQ((v2 - v1).y, -2.0);
	ASSERT_DOUBLE_EQ((v2 - v1).z, -2.0);
	ASSERT_DOUBLE_EQ((v2 - v1).length(), 2 * std::sqrt(3.0));

	Vector3D v4(Point3D(3, 0, 0), Point3D(3, 4, 0));
	Vector3D v5(p1, Point3D(3, 4, 0));
	Vector3D v3 = v5 - v4;		// Calculate the smaller side of 2D-Egyptian triangle
	ASSERT_DOUBLE_EQ(v3.x, 3.0);
	ASSERT_DOUBLE_EQ(v3.y, 0.0);
	ASSERT_DOUBLE_EQ(v3.z, 0.0);

	Vector3D v6 = v1 - v1;
	ASSERT_DOUBLE_EQ(v6.x, 0.0);
	ASSERT_DOUBLE_EQ(v6.y, 0.0);
	ASSERT_DOUBLE_EQ(v6.z, 0.0);
}

TEST(Vector3D, OperatorMultiplyByScalar) {
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);

	Vector3D v1(p1, p2);
	Vector3D v2(p2, p1);
	Vector3D v3 = v1 * 10;
	ASSERT_DOUBLE_EQ(v3.x, 10.0);
	ASSERT_DOUBLE_EQ(v3.y, 10.0);
	ASSERT_DOUBLE_EQ(v3.z, 10.0);
	v3 = v1 * (-10.5);
	ASSERT_DOUBLE_EQ(v3.x, -10.5);
	ASSERT_DOUBLE_EQ(v3.y, -10.5);
	ASSERT_DOUBLE_EQ(v3.z, -10.5);

	v3 = v2 * (-10.5);
	ASSERT_DOUBLE_EQ(v3.x, 10.5);
	ASSERT_DOUBLE_EQ(v3.y, 10.5);
	ASSERT_DOUBLE_EQ(v3.z, 10.5);
	v3 = v2 * 10.5;
	ASSERT_DOUBLE_EQ(v3.x, -10.5);
	ASSERT_DOUBLE_EQ(v3.y, -10.5);
	ASSERT_DOUBLE_EQ(v3.z, -10.5);
}

TEST(Vector3D, Dot) {
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);

	Vector3D v1(p1, p2);
	Vector3D v2(p2, p1);
	double dot = v1.dot(v2);
	Vector3D v4(Point3D(1e+6, 0, 0), Point3D(-1e+6, 0, 0));
	Vector3D v5(Point3D(0, 1e+6, 0), Point3D(0, -1e+6, 0));
	dot = v4.dot(v5);
	ASSERT_DOUBLE_EQ(dot, 0.0);
}

