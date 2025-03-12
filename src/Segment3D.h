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
            return start.distanceTo(other.start); // Distance between two points
        }

        if (isZeroLength()) {
            return pointToSegmentDistance(start, other); // Distance from a point to a segment
        }

        if (other.isZeroLength()) {
            return pointToSegmentDistance(other.start, *this); // Distance from a point to a segment
        }

        Vector3D u = Vector3D(start, end);
        Vector3D v = Vector3D(other.start, other.end);
        Vector3D w = Vector3D(start, other.start);

        double a = u.dot(u); // |u|^2
        double b = u.dot(v); // u.v
        double c = v.dot(v); // |v|^2
        double d = u.dot(w); // u.w
        double e = v.dot(w); // v.w

        double D = a * c - b * b;

        // Segments are parallel (or nearly parallel)
        if (D < EPSILON) {
            // Return the minimum distance from one segment's endpoints to the other segment
            double dist1 = pointToSegmentDistance(start, other);
            double dist2 = pointToSegmentDistance(end, other);
            double dist3 = pointToSegmentDistance(other.start, *this);
            double dist4 = pointToSegmentDistance(other.end, *this);

            return std::min(std::min(dist1, dist2), std::min(dist3, dist4));
        }

        // Parameters for the nearest points on the segments
        double sN = (b * e - c * d) / D;
        double tN = (a * e - b * d) / D;

        // Clamp sN and tN to [0,1]
        double sD = D;       // prevent division by zero
        double tD = D;

        // Clamp parameters to the segment
        if (sN < 0.0) {        // sc < 0 => the s=0 edge is visible
            sN = 0.0;
            tN = e / c;
            tN = (tN < 0.0) ? 0.0 : ((tN > 1.0) ? 1.0 : tN);
        }
        else if (sN > 1.0) {  // sc > 1 => the s=1 edge is visible
            sN = 1.0;
            tN = (e + b) / c;
            tN = (tN < 0.0) ? 0.0 : ((tN > 1.0) ? 1.0 : tN);
        }

        if (tN < 0.0) {           // tc < 0 => the t=0 edge is visible
            tN = 0.0;
            sN = d / a;
            sN = (sN < 0.0) ? 0.0 : ((sN > 1.0) ? 1.0 : sN);
        }
        else if (tN > 1.0) {     // tc > 1 => the t=1 edge is visible
            tN = 1.0;
            sN = (d + b) / a;
            sN = (sN < 0.0) ? 0.0 : ((sN > 1.0) ? 1.0 : sN);
        }

        Point3D closestPoint1 = Point3D(start.x + sN * u.x, start.y + sN * u.y, start.z + sN * u.z);
        Point3D closestPoint2 = Point3D(other.start.x + tN * v.x, other.start.y + tN * v.y, other.start.z + tN * v.z);

        return closestPoint1.distanceTo(closestPoint2);
    }

private:
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
