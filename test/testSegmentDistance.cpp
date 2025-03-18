#include <gtest/gtest.h>

#include "Point3D.h"
#include "Vector3D.h"
#include "Segment3D.h"


TEST(Point3D, CreatePoint){
	ASSERT_NO_THROW(Point3D p1(0, 0, 0));
	ASSERT_NO_THROW(Point3D p1(1, 1, 1));
}

TEST(Segment3D, CreateSegment){
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	Point3D p3(0, 1, 0);
	Point3D p4(1, 0, 1);
	ASSERT_NO_THROW(Segment3D seg1(p1, p1));
	ASSERT_NO_THROW(Segment3D seg1(p1, p2));
	ASSERT_NO_THROW(Segment3D seg2(p3, p4));
}

TEST(Segment3D, Zero_Segments) {
	Point3D p1(0, 0, 0);
	Point3D p3(1, 0, 0);

	Segment3D seg1(p1, p1);
	Segment3D seg2(p3, p3);

	double distance = seg1.distanceTo(seg1);
	ASSERT_DOUBLE_EQ(distance, 0.0);

	distance = seg1.distanceTo(seg2);
	std::cout << "Distance between segments: " << distance << std::endl;

	ASSERT_DOUBLE_EQ(distance, 1.0);

	Point3D p2(4, 5, 6);
	Segment3D s3(p1, p1);
	Segment3D s4(p2, p2);
	ASSERT_DOUBLE_EQ(s3.distanceTo(s4), p1.distanceTo(p2)) << "Distance between zero segments should be equal to distance between points";
}

TEST(Segment3D, Zero_Segments_NegCoords) {
	Point3D p1(0, 0, 0);
	Point3D p3(-1, 0, 0);

	Segment3D seg1(p1, p1);
	Segment3D seg2(p3, p3);

	double distance = seg1.distanceTo(seg1);
	ASSERT_DOUBLE_EQ(distance, 0.0);

	distance = seg1.distanceTo(seg2);
	std::cout << "Distance between segments: " << distance << std::endl;

	ASSERT_DOUBLE_EQ(distance, 1.0);

	Point3D p2(-4, -5, -6);
	Segment3D s3(p1, p1);
	Segment3D s4(p2, p2);
	ASSERT_DOUBLE_EQ(s3.distanceTo(s4), p1.distanceTo(p2)) << "Distance between zero segments should be equal to distance between points";

	Point3D p4(4, -5, -6);
	Segment3D s5(p1, p4);
	Segment3D s6(p2, p4);
	ASSERT_DOUBLE_EQ(s5.distanceTo(s6), 0.0);
	Segment3D s7(p2, p3);
	ASSERT_DOUBLE_EQ(s7.distanceTo(s5), 1.0);
	ASSERT_DOUBLE_EQ(s5.distanceTo(s7), 1.0);
}

TEST(Segment3D, SelfDist) {
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 0);
	Segment3D seg1(p1, p2);
	double distance = seg1.distanceTo(seg1);
	ASSERT_DOUBLE_EQ(distance, 0.0);
}

TEST(Segment3D, SelfDist_NegCoords) {
	Point3D p1(0, 0, 0);
	Point3D p2(-1, -1, 0);
	Segment3D seg1(p1, p2);
	double distance = seg1.distanceTo(seg1);
	ASSERT_DOUBLE_EQ(distance, 0.0);
}

TEST(Segment3D, PointToSegmentDistance) {
	Point3D p(0, 0, 0);
	Segment3D seg(Point3D(1, 0, 0), Point3D(2, 0, 0));
	ASSERT_DOUBLE_EQ(seg.distanceTo(Segment3D(p, p)), 1.0);

	Point3D p2(2, 10, 0);
	Segment3D seg2(Point3D(0, 0, 0), Point3D(3, 0, 0));
	ASSERT_DOUBLE_EQ(seg2.distanceTo(Segment3D(p2, p2)), 10.0);
}

TEST(Segment3D, PointToSegmentDistance_NegCoords) {
	Point3D p(0, 0, 0);
	Segment3D seg(Point3D(-1, 0, 0), Point3D(2, 0, 0));
	ASSERT_DOUBLE_EQ(seg.distanceTo(Segment3D(p, p)), 0.0); // Distance to point on the segment

	Point3D p2(0, -10, 0);
	Segment3D seg2(Point3D(-1, 0, 0), Point3D(2, 0, 0));
	ASSERT_DOUBLE_EQ(seg2.distanceTo(Segment3D(p2, p2)), 10.0);
}

TEST(Segment3D, ParallelSegments) {
	Segment3D seg1(Point3D(0, 0, 0), Point3D(1, 0, 0));
	Segment3D seg2(Point3D(0, 1, 0), Point3D(1, 1, 0));
	ASSERT_DOUBLE_EQ(seg1.distanceTo(seg2), 1.0);

	Segment3D seg3(Point3D(0, 0, 0), Point3D(1, 0, 0));
	Segment3D seg4(Point3D(0, 0, 0), Point3D(3, 0, 0)); // Collinear, overlapping
	double distance = seg3.distanceTo(seg4);
	std::cout << __LINE__ << " Distance between segments: " << distance << std::endl;
	ASSERT_DOUBLE_EQ(seg3.distanceTo(seg4), 0.0);
	
	Segment3D seg5(Point3D(0, 0, 0), Point3D(1, 0, 0));
	Segment3D seg6(Point3D(2, 0, 0), Point3D(3, 0, 0)); // Collinear, non-overlapping
	ASSERT_DOUBLE_EQ(seg5.distanceTo(seg6), 1.0);

	Segment3D seg7(Point3D(0, 1, 1), Point3D(1, 1, 1));

	double expectedDistance = std::sqrt(2.0);
	ASSERT_DOUBLE_EQ(seg1.distanceTo(seg7), expectedDistance);
}

TEST(Segment3D, ParallelSegments_NegCoords) {
	Segment3D seg1(Point3D(0, 0, 0), Point3D(-1, 0, 0));
	Segment3D seg2(Point3D(0, -1, 0), Point3D(-1, -1, 0));
	ASSERT_DOUBLE_EQ(seg1.distanceTo(seg2), 1.0);

	Segment3D seg3(Point3D(0, 0, 0), Point3D(-1, 0, 0));
	Segment3D seg4(Point3D(0, 0, 0), Point3D(-3, 0, 0)); // Collinear, overlapping
	ASSERT_DOUBLE_EQ(seg3.distanceTo(seg4), 0.0);

	Segment3D seg5(Point3D(-1, -1, 0), Point3D(1, 1, 0));
	Segment3D seg6(Point3D(-2, -2, 0), Point3D(3, 3, 0)); // Collinear, overlapping
	ASSERT_DOUBLE_EQ(seg5.distanceTo(seg6), 0.0);

	Segment3D seg7(Point3D(0, 0, 0), Point3D(-1, 0, 0));
	Segment3D seg8(Point3D(-2, 0, 0), Point3D(-3, 0, 0)); // Collinear, non-overlapping
	ASSERT_DOUBLE_EQ(seg7.distanceTo(seg8), 1.0);

	double expectedDistance = std::sqrt(2.0);

	Segment3D seg9(Point3D(-1, -1, 0), Point3D(1, 1, 0));
	Segment3D seg10(Point3D(-3, -3, 0), Point3D(-2, -2, 0)); // Collinear, non-overlapping
	ASSERT_DOUBLE_EQ(seg9.distanceTo(seg10), expectedDistance);

	Segment3D seg11(Point3D(0, 1, 1), Point3D(1, 1, 1));

	ASSERT_DOUBLE_EQ(seg1.distanceTo(seg11), expectedDistance);
}

TEST(Segment3D, IntersectingSegments) {
	Segment3D s1(Point3D(0, 0, 0), Point3D(1, 1, 0));
	Segment3D s2(Point3D(0, 1, 0), Point3D(1, 0, 0));
	EXPECT_NEAR(s1.distanceTo(s2), 0.0, 1e-6);
}

TEST(Segment3D, SkewSegments) {
	Segment3D seg1(Point3D(0, 1, 0), Point3D(1, 0, 0));
	Segment3D seg2(Point3D(0, 0, 1), Point3D(1, 1, 1));

	// Calculate the expected distance (which is equal to z = 1 in this partial case)
	double expectedDistance = 1.0;
	ASSERT_DOUBLE_EQ(seg1.distanceTo(seg2), expectedDistance);
}

TEST(Segment3D, GeneralCase) {
	Segment3D s1(Point3D(0, 0, 0), Point3D(2, 0, 0));
	Segment3D s2(Point3D(1, 1, 0), Point3D(1, 2, 0));
	ASSERT_DOUBLE_EQ(s1.distanceTo(s2), 1.0);
}

TEST(Segment3D, PerpendicularSegments) {
	Segment3D s1(Point3D(0, 0, 0), Point3D(1, 0, 0));
	Segment3D s2(Point3D(0, 0, 0), Point3D(0, 1, 0));

	// The segments intersect at (0, 0, 0), so the distance should be 0
	ASSERT_DOUBLE_EQ(s1.distanceTo(s2), 0.0);

	// Non-intersecting perpendicular segments
	Segment3D s3(Point3D(0, 1, 0), Point3D(0, 2, 0));
	ASSERT_DOUBLE_EQ(s1.distanceTo(s3), 1.0);

}

TEST(Segment3D, CollinearOverlappingSegments) {
	Segment3D s1(Point3D(0, 0, 0), Point3D(2, 0, 0));
	Segment3D s2(Point3D(1, 0, 0), Point3D(3, 0, 0));
	ASSERT_DOUBLE_EQ(s1.distanceTo(s2), 0.0);
}

TEST(Segment3D, CollinearNonOverlappingSegments) {
	Segment3D s1(Point3D(0, 0, 0), Point3D(1, 0, 0));
	Segment3D s2(Point3D(2, 0, 0), Point3D(3, 0, 0));
	ASSERT_DOUBLE_EQ(s1.distanceTo(s2), 1.0); // Distance is 1 since closest points are (1,0,0) and (2,0,0)
}


TEST(Segment3D, ArbitraryCalculations){
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 0);
	Point3D p3(1, 0, 0);
	Point3D p4(1, 1, 1);
	
	Segment3D seg1(p1, p1);
	Segment3D seg2(p3, p3);

	double distance = seg1.distanceTo(seg2);
	std::cout << "Distance between segments (1-2): " << distance << std::endl;
	
	EXPECT_EQ(distance, 1);
	
	Segment3D seg3(p1, p3);
	Segment3D seg4(p2, p4);
	
	distance = seg3.distanceTo(seg4);
	std::cout << "2. Distance between segments (3-4): " << distance << std::endl;
	
	ASSERT_DOUBLE_EQ(distance, 1.0);	
}

