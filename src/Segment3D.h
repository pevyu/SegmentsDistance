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

    Segment3D(const Point3D& start, const Point3D& end) : start(start), end(end) {}

    float distanceTo(const Segment3D& other) const {
        Vector3D u = Vector3D(start, end); // Vector of this segment
        Vector3D v = Vector3D(other.start, other.end); // Vector of other segment
        Vector3D w = Vector3D(start, other.start); // Vector between starts of segments

        float a = u.dot(u); // |u|^2
        float b = u.dot(v); // u.v
        float c = v.dot(v); // |v|^2
        float d = u.dot(w); // u.w
        float e = v.dot(w); // v.w

        float D = a * c - b * b; // the determinant

        // if the segments are parallel
        if (D < std::numeric_limits<float>::epsilon()) {
            // return distance from one endpoint to the other segment
            return pointToSegmentDistance(start, other) < pointToSegmentDistance(end, other) ?
                pointToSegmentDistance(start, other) :
                pointToSegmentDistance(end, other);
        }

        // Parameters for the nearest points on the segments
        float sN = (b * e - c * d) / D;
        float tN = (a * e - b * d) / D;

        // Clamp tN to [0,1]
        if (tN < 0) tN = 0;
        else if (tN > 1) tN = 1;

        // Clamp sN to [0,1]
        if (sN < 0) {
            sN = 0;
            tN = e < 0 ? 1 : 0;
        } else if (sN > 1) {
            sN = 1;
            tN = (b + e) < 0 ? 1 : 0;
        }

        Point3D closestPoint1 = Point3D(start.x + sN * u.x, start.y + sN * u.y, start.z + sN * u.z);
        Point3D closestPoint2 = Point3D(other.start.x + tN * v.x, other.start.y + tN * v.y, other.start.z + tN * v.z);

        return closestPoint1.distanceTo(closestPoint2);
    }

private:
    float pointToSegmentDistance(const Point3D& p, const Segment3D& s) const {
        Vector3D v = Vector3D(s.start, s.end);
        Vector3D w = Vector3D(s.start, p);
        float c1 = w.dot(v);
		float c2 = v.dot(v);
        float b = c1 / c2;

        if (b < 0) return p.distanceTo(s.start); // Beyond the 'start' of the segment
        else if (b > 1) return p.distanceTo(s.end); // Beyond the 'end' of the segment

        Point3D Pb(s.start.x + b * v.x, s.start.y + b * v.y, s.start.z + b * v.z);
        return p.distanceTo(Pb); // Return the distance to the closest point
    }
};

#endif // SEGMENT3D_H
