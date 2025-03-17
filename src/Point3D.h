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

    Point3D operator-(const Point3D& other) const {
        return Point3D(x - other.x, y - other.y, z - other.z);
    }

    double distanceTo(const Point3D& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    double distanceTo(const Geometry* other) const override {
        const Point3D* otherPoint = dynamic_cast<const Point3D*>(other);
        if (otherPoint == nullptr) {
            // if the other is not point, then what the distance we should return?
            return -1;
        }
        return distanceTo(*otherPoint);
    }

    //Point3D* clone() const override { return new Point3D(*this); }
};

#endif // POINT3D_H
