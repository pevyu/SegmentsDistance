#include <gtest/gtest.h>

#include "Point3D.h"

TEST(Point3D, CreatePoint){
	ASSERT_NO_THROW(Point3D p1(0, 0, 0));
	ASSERT_NO_THROW(Point3D p1(1, 1, 1));
}

TEST(Vector3D, DistanceTo){
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	
    ASSERT_DOUBLE_EQ(p1.distanceTo(p2), std::sqrt(3.0));
}

