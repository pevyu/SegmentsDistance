// File Segment3D.h
// definition of Segment3D class

#ifndef SEGMENT3D_H
#define SEGMENT3D_H

#include <cmath>
#include <limits>

#include "Point3D.h"
#include "Vector3D.h"

class Segment3D {
public:
    Point3D start, end;
    static constexpr double EPSILON = 1e-9;

    Segment3D(const Point3D& start, const Point3D& end) : start(start), end(end) {}

    bool isZeroLength() const {
        return start.distanceTo(end) < EPSILON;
    }

double distanceTo(const Segment3D& other) const {
    if (isZeroLength() && other.isZeroLength()) {
        return start.distanceTo(other.start);
    }

    if (isZeroLength()) {
        return pointToSegmentDistance(start, other);
    }

    if (other.isZeroLength()) {
        return pointToSegmentDistance(other.start, *this);
    }

    Vector3D u = Vector3D(start, end);
    Vector3D v = Vector3D(other.start, other.end);
    Vector3D w = Vector3D(start, other.start);

    double a = u.dot(u);
    double b = u.dot(v);
    double c = v.dot(v);
    double d = u.dot(w);
    double e = v.dot(w);

    double D = a * c - b * b;

    if (D < EPSILON) {
        // Parallel or nearly parallel
        double dist1 = pointToSegmentDistance(start, other);
        double dist2 = pointToSegmentDistance(end, other);
        double dist3 = pointToSegmentDistance(other.start, *this);
        double dist4 = pointToSegmentDistance(other.end, *this);
        return std::min(std::min(dist1, dist2), std::min(dist3, dist4));
    }

    // Parameters for the nearest points on the segments
    double sN = (b * e - c * d);
    double tN = (a * e - b * d);
    double sD = D;
    double tD = D;

    // Clamp sN and tN to the interval [0, D]
    bool s_is_clamped = false;
    bool t_is_clamped = false;

    if (sN < 0.0) {
        sN = 0.0;
        s_is_clamped = true;
    } else if (sN > sD) {
        sN = sD;
        s_is_clamped = true;
    }

    if (tN < 0.0) {
        tN = 0.0;
        t_is_clamped = true;
    } else if (tN > tD) {
        tN = tD;
        t_is_clamped = true;
    }
    
    Point3D closestPoint1;
    Point3D closestPoint2;

    if (s_is_clamped || t_is_clamped) {
        // If either s or t is clamped, we need to recompute the distance
        if (s_is_clamped && t_is_clamped) {
            // Both are clamped, the closest points are endpoints of the segments.
             closestPoint1 = (sN == 0.0) ? start : end;
             closestPoint2 = (tN == 0.0) ? other.start : other.end;
        } else if (s_is_clamped) {
            closestPoint1 = (sN == 0.0) ? start : end;
            closestPoint2 = calculateClosestPoint(closestPoint1, other);
        } else {
             closestPoint2 = (tN == 0.0) ? other.start : other.end;
             closestPoint1 = calculateClosestPoint(closestPoint2, *this);
        }

    }
    else {
        closestPoint1 = Point3D(start.x + (sN / sD) * u.x, start.y + (sN / sD) * u.y, start.z + (sN / sD) * u.z);
        closestPoint2 = Point3D(other.start.x + (tN / tD) * v.x, other.start.y + (tN / tD) * v.y, other.start.z + (tN / tD) * v.z);
    }

    return closestPoint1.distanceTo(closestPoint2);
}

private:
	Point3D calculateClosestPoint(const Point3D& point, const Segment3D& segment) const {
		Vector3D segmentVector = Vector3D(segment.start, segment.end);
		Vector3D pointVector = Vector3D(segment.start, point);
		double t = pointVector.dot(segmentVector) / segmentVector.dot(segmentVector);

		if (t < 0) {
			return segment.start;
		} else if (t > 1) {
			return segment.end;
		} else {
			return Point3D(segment.start.x + t * segmentVector.x,
						   segment.start.y + t * segmentVector.y,
						   segment.start.z + t * segmentVector.z);
		}
	}

    double pointToSegmentDistance(const Point3D& p, const Segment3D& s) const {
        Vector3D v = Vector3D(s.start, s.end);
        Vector3D w = Vector3D(s.start, p);
        double c1 = w.dot(v);
        double c2 = v.dot(v);

        // If the segment is effectively a point, return distance to that point.
        if (c2 < EPSILON) {
            return p.distanceTo(s.start);
        }

        double b = c1 / c2;

        if (b < 0) return p.distanceTo(s.start);
        else if (b > 1) return p.distanceTo(s.end);

        Point3D Pb(s.start.x + b * v.x, s.start.y + b * v.y, s.start.z + b * v.z);
        return p.distanceTo(Pb);
    }
};

#endif // SEGMENT3D_H
