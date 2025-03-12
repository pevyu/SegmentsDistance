// File Point3D.h
// definition of Point3D class

#ifndef POINT3D_H
#define POINT3D_H
#include <cmath>

class Point3D {
public:
    double x, y, z;

    Point3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    Point3D operator-(const Point3D& other) const {
        return Point3D(x - other.x, y - other.y, z - other.z);
    }

    double distanceTo(const Point3D& other) const {
        return std::sqrt((x - other.x) * (x - other.x) + 
                         (y - other.y) * (y - other.y) + 
                         (z - other.z) * (z - other.z));
    }
};

#endif // POINT3D_H
