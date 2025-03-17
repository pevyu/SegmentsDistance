// File Segment3D.h
// definition of Segment3D class

#ifndef SEGMENT3D_H
#define SEGMENT3D_H

#include <cmath>
#include <limits>
#include <algorithm>

#include "Point3D.h"
#include "Vector3D.h"

class Segment3D : public Geometry {
    bool hasZeroLength;
public:
    Point3D start, end;

    Segment3D(const Point3D& start, const Point3D& end) : start(start), end(end), hasZeroLength(start.distanceTo(end) < EPSILON) {}

    double distanceTo(const Segment3D& other) const {
        if (hasZeroLength) {
            return pointToSegmentDistance(start, other);
        }
        if (other.hasZeroLength) {
            return pointToSegmentDistance(other.start, *this);
        }
        if (&other == this) {
            return 0.0;
        }
        Vector3D p1 = Vector3D(start.x, start.y, start.z);
        Vector3D q1 = Vector3D(end.x, end.y, end.z);
        Vector3D p2 = Vector3D(other.start.x, other.start.y, other.start.z);
        Vector3D q2 = Vector3D(other.end.x, other.end.y, other.end.z);
        Vector3D d1 = q1 - p1; // Direction vector of segment 1
        Vector3D d2 = q2 - p2; // Direction vector of segment 2
        Vector3D r = p1 - p2;

        double a = d1.dot(d1);
        double b = d1.dot(d2);
        double c = d2.dot(d2);
        double d = d1.dot(r);
        double e = d2.dot(r);
        double f = a * c - b * b;

        double s, t;

        // If segments are not parallel, compute closest point on L1 to L2 and
        // clamp to segment S1.  Otherwise, pick arbitrary s (e.g., 0)
        if (f < EPSILON) {        // S1 and S2 are nearly parallel
            s = 0.0;
        }
        else {
            s = (b * e - c * d) / f;
            s = std::clamp(s, 0.0, 1.0); // Clamp s to [0, 1]
        }
        // Then compute closest point on L2 to S1(s)
        t = (b * s + e) / c;

        // If t in [0,1] done. else clamp t, recompute s for the new value
        if (t < 0.0) {
            t = 0.0;
            s = std::clamp(-d / a, 0.0, 1.0);
        }
        else if (t > 1.0) {
            t = 1.0;
            s = std::clamp((b - d) / a, 0.0, 1.0);
        }

        Vector3D c1 = p1 + d1 * s;
        Vector3D c2 = p2 + d2 * t;

        return (c1 - c2).length();
    }

    double distanceTo(const Geometry* other) const override {
        const Segment3D* otherSegment = dynamic_cast<const Segment3D*>(other);
        if (nullptr == otherSegment) {
            return std::numeric_limits<double>::infinity();
        }

        return distanceTo(otherSegment);
    }

    ~Segment3D() override {}

private:
    Point3D calculateClosestPoint(const Point3D& point, const Segment3D& segment) const {
        Vector3D segmentVector = Vector3D(segment.start, segment.end);
        Vector3D pointVector = Vector3D(segment.start, point);
        double t = pointVector.dot(segmentVector) / segmentVector.dot(segmentVector);

        if (t < 0) {
            return segment.start;
        }
        else if (t > 1) {
            return segment.end;
        }
        else {
            return Point3D(segment.start.x + t * segmentVector.x,
                segment.start.y + t * segmentVector.y,
                segment.start.z + t * segmentVector.z);
        }
    }

    double pointToSegmentDistance(const Point3D& p, const Segment3D& s) const {
        if (s.hasZeroLength) {
            return p.distanceTo(s.start);
        }
        Vector3D v = Vector3D(s.start, s.end);
        Vector3D w = Vector3D(s.start, p);
        double c1 = w.dot(v);
        double c2 = v.dot(v);

        // If the segment is effectively a point, return distance to that point.
        if (c2 < EPSILON) {
            return p.distanceTo(s.start);
        }

        double b = c1 / c2;

        if (b < 0) {
            return p.distanceTo(s.start);
        } else if (b > 1) {
            return p.distanceTo(s.end);
        }

        Point3D Pb(s.start.x + b * v.x, s.start.y + b * v.y, s.start.z + b * v.z);
        return p.distanceTo(Pb);
    }
};

#endif // SEGMENT3D_H
