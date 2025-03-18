// File Vector3D.h
// definition of Vector3D class

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Point3D.h"

class Vector3D: public Geometry {
public:
    double x, y, z;
    bool hasZeroLength;

    Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z), hasZeroLength(length() < Geometry::EPSILON) {}
    Vector3D(const Point3D& start, const Point3D& end) 
        : x(end.x - start.x), y(end.y - start.y), z(end.z - start.z), hasZeroLength(start.distanceTo(end) < Geometry::EPSILON) {};

    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D operator*(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    double dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    double distanceTo(const Geometry& other) const override {
        const Vector3D* otherVector = dynamic_cast<const Vector3D*>(&other);
        if (nullptr == otherVector) {
            return std::numeric_limits<double>::infinity();
        }
        // for shure, I don't know what to return in this case...
        return (Vector3D(x - otherVector->x, y - otherVector->y, z - otherVector->z)).length();
    }

};

#endif // VECTOR3D_H

