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

TEST(Zero_Segments, CalculateDistance){
	Point3D p1(0, 0, 0);
    Point3D p3(1, 0, 0);
	
	Segment3D seg1(p1, p1);
	Segment3D seg2(p3, p3);

	float distance = seg1.distanceTo(seg2);
    std::cout << "Distance between segments: " << distance << std::endl;
	
	ASSERT_EQ(distance, 1); // failed, but what shuild it be the value?
		
}

TEST(Segments, CalculateDistance){
	Point3D p1(0, 0, 0);
    Point3D p2(1, 1, 0);
    Point3D p3(1, 0, 0);
    Point3D p4(1, 1, 1);
	
	Segment3D seg1(p1, p1);
	Segment3D seg2(p3, p3);

	float distance = seg1.distanceTo(seg2);
    std::cout << "Distance between segments (1-2): " << distance << std::endl;
	
	EXPECT_EQ(distance, 1);
	
	Segment3D seg3(p1, p3);
	Segment3D seg4(p2, p4);
	
	distance = seg3.distanceTo(seg4);
    std::cout << "2. Distance between segments (3-4): " << distance << std::endl;
	
	ASSERT_FLOAT_EQ(distance, sqrt(2));
	
}

