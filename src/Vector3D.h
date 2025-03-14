// File Vector3D.h
// definition of Vector3D class

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Point3D.h"

class Vector3D {
public:
    double x, y, z;

    Vector3D(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
    Vector3D(const Point3D& start, const Point3D& end) 
        : x(end.x - start.x), y(end.y - start.y), z(end.z - start.z) {};

    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

	// unary minus (change of sign / direction)
    Vector3D operator-() const {
        return Vector3D(-x, -y, -z);
    }

    Vector3D operator*(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    friend Vector3D operator*(double scalar, const Vector3D& vector) {
        return vector * scalar; // Используем уже определенный оператор
    }

    Vector3D operator/(double scalar) const {
        if (scalar == 0.0) {
            // Обработка деления на ноль (можно выбросить исключение или вернуть вектор с NaN)
            return Vector3D(std::numeric_limits<double>::quiet_NaN(),
                            std::numeric_limits<double>::quiet_NaN(),
                            std::numeric_limits<double>::quiet_NaN());
        }
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }

    Vector3D& operator+=(const Vector3D& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3D& operator-=(const Vector3D& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3D& operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3D& operator/=(double scalar) {
       if (scalar == 0.0) {
            // Обработка деления на ноль
            x = std::numeric_limits<double>::quiet_NaN();
            y = std::numeric_limits<double>::quiet_NaN();
            z = std::numeric_limits<double>::quiet_NaN();
            return *this;
        }
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    bool operator==(const Vector3D& other) const {
        return (std::abs(x - other.x) < DBL_EPSILON &&
                std::abs(y - other.y) < DBL_EPSILON &&
                std::abs(z - other.z) < DBL_EPSILON);
    }

    // Оператор сравнения на неравенство
    bool operator!=(const Vector3D& other) const {
        return !(*this == other);
    }
    double dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3D cross(const Vector3D& other) const {
        return Vector3D(y * other.z - z * other.y,
                        z * other.x - x * other.z,
                        x * other.y - y * other.x);
    }

    double length() const {
        return std::sqrt(x * x + y * y + z * z);
    }
};

#endif // VECTOR3D_H

