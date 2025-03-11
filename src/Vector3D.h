// File Vector3D.h
// definition of Vector3D class

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Point3D.h"

class Vector3D {
public:
    float x, y, z;

    Vector3D(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    Vector3D(const Point3D& start, const Point3D& end) 
        : x(end.x - start.x), y(end.y - start.y), z(end.z - start.z) {}

    float dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3D cross(const Vector3D& other) const {
        return Vector3D(y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x);
    }

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
};

#endif // VECTOR3D_H

