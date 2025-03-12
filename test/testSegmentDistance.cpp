#include <gtest/gtest.h>

#include "Point3D.h"
#include "Vector3D.h"
#include "Segment3D.h"


TEST(Point3D, CreatePoint){
	ASSERT_NO_THROW(Point3D p1(0, 0, 0));
	ASSERT_NO_THROW(Point3D p1(1, 1, 1));
}

TEST(Vector3D, CreateVector){
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	ASSERT_NO_THROW(Vector3D v(p1, p2));
	ASSERT_NO_THROW(Vector3D v(p2, p1));
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

TEST(Segment3D, Zero_Segments){
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

TEST(Segment3D, SelfDist){
	Point3D p1(0, 0, 0);
    Point3D p2(1, 1, 0);
	Segment3D seg1(p1, p2);
	double distance = seg1.distanceTo(seg1);
	ASSERT_DOUBLE_EQ(distance, 0.0);
}

TEST(Segment3D, PointToSegmentDistance) {
    Point3D p(0, 0, 0);
    Segment3D seg(Point3D(1, 0, 0), Point3D(2, 0, 0));
    ASSERT_DOUBLE_EQ(seg.distanceTo(Segment3D(p, p)), 1.0);
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

}

TEST(Segment3D, IntersectingSegments) {
    Segment3D s1(Point3D(0, 0, 0), Point3D(1, 1, 0));
    Segment3D s2(Point3D(0, 1, 0), Point3D(1, 0, 0));
    ASSERT_DOUBLE_EQ(s1.distanceTo(s2), 0.0);
}


TEST(Segments, CalculateDistance){
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
	
	ASSERT_DOUBLE_EQ(distance, sqrt(2.0f));
	
}

