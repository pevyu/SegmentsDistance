// File Point3D.h
// definition of Point3D class

#ifndef POINT3D_H
#define POINT3D_H
#include <cmath>

#include "Geometry.h"

class Point3D:public Geometry {
public:
    double x, y, z;

    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    double distanceTo(const Point3D& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    double distanceTo(const Geometry& other) const override {
        const Point3D* otherPoint = dynamic_cast<const Point3D*>(&other);
        if (otherPoint == nullptr) {
            // if the other is not point, then what the distance we should return?
            return -1; // also, for example, it can be std::numeric_limits<double>::infinity()
        }
        return distanceTo(*otherPoint);
    }

};

#endif // POINT3D_H
