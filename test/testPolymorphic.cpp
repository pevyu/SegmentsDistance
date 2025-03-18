#include <gtest/gtest.h>

#include "Segment3D.h"

// The polymorphism is not fully implemented, yet.
// So, just handle unacceptable cases without any calculations

TEST(Polimorphic, PointToVectorDistance) {
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	Point3D p3(10, 10, 1);

	Vector3D v1(p2, p3);

	ASSERT_DOUBLE_EQ(p1.distanceTo(v1), -1);

}

TEST(Polimorphic, VectorToPointDistance) {
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	Point3D p3(10, 10, 1);

	Vector3D v1(p2, p3);

	ASSERT_DOUBLE_EQ(v1.distanceTo(p1), std::numeric_limits<double>::infinity());
}

TEST(Polimorphic, PointToSegmentDistance) {
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	Point3D p3(10, 10, 1);

	Segment3D s1(p2, p3);

	ASSERT_DOUBLE_EQ(p1.distanceTo(s1), -1);

}

TEST(Polimorphic, SegmentToPointDistance) {
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	Point3D p3(10, 10, 1);

	Segment3D s1(p2, p3);

	ASSERT_DOUBLE_EQ(s1.distanceTo(p1), std::numeric_limits<double>::infinity());
}

TEST(Polimorphic, VectorToSegmentDistance) {
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	Point3D p3(10, 10, 1);

	Vector3D v1(p1, p2);
	Segment3D s1(p2, p3);

	ASSERT_DOUBLE_EQ(v1.distanceTo(s1), std::numeric_limits<double>::infinity());
}

TEST(Polimorphic, SegmentToVectorDistance) {
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	Point3D p3(10, 10, 1);

	Vector3D v1(p1, p2);
	Segment3D s1(p2, p3);

	ASSERT_DOUBLE_EQ(s1.distanceTo(v1), std::numeric_limits<double>::infinity());
}

