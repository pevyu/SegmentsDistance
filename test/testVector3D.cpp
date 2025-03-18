#include <gtest/gtest.h>

#include "Vector3D.h"

TEST(Vector3D, hasZeroLength){
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	
    Vector3D v1(p1, p1);
    Vector3D v2(p1, p2);
	
	ASSERT_DOUBLE_EQ(v1.x, 0.0);
	ASSERT_DOUBLE_EQ(v1.y, 0.0);
	ASSERT_DOUBLE_EQ(v1.z, 0.0);
	ASSERT_TRUE(v1.hasZeroLength);
	
	ASSERT_DOUBLE_EQ(v2.x, 1.0);
	ASSERT_DOUBLE_EQ(v2.y, 1.0);
	ASSERT_DOUBLE_EQ(v2.z, 1.0);
	ASSERT_FALSE(v2.hasZeroLength);
}

TEST(Vector3D, OperatorPlus){
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	
	Vector3D v1(p1, p2);
	Vector3D v2(p2, p1);
	
	ASSERT_DOUBLE_EQ((v1 + v2).x, 0.0);
	ASSERT_DOUBLE_EQ((v1 + v2).y, 0.0);
	ASSERT_DOUBLE_EQ((v1 + v2).z, 0.0);
	ASSERT_DOUBLE_EQ((v1 + v2).length(), 0.0);
	ASSERT_DOUBLE_EQ((v2 + v1).x, 0.0);
	ASSERT_DOUBLE_EQ((v2 + v1).y, 0.0);
	ASSERT_DOUBLE_EQ((v2 + v1).z, 0.0);
	ASSERT_DOUBLE_EQ((v2 + v1).length(), 0.0);
	
	Vector3D v3(p1, Point3D(3,0,0));
	Vector3D v4(Point3D(3,0,0), Point3D(3,4,0));
	Vector3D v5 = v3 + v4;		// 2D-Egyptian triangle
	ASSERT_DOUBLE_EQ(v5.x, 3.0);
	ASSERT_DOUBLE_EQ(v5.y, 4.0);
	ASSERT_DOUBLE_EQ(v5.z, 0.0);
	ASSERT_DOUBLE_EQ(v5.length(), 5.0);
    Vector3D v6 = v1 + v1;
	ASSERT_DOUBLE_EQ(v6.x, 2.0);
	ASSERT_DOUBLE_EQ(v6.y, 2.0);
	ASSERT_DOUBLE_EQ(v6.z, 2.0);
}

TEST(Vector3D, OperatorMinus){
	Point3D p1(0, 0, 0);
	Point3D p2(1, 1, 1);
	
	Vector3D v1(p1, p2);
	Vector3D v2(p2, p1);
	
	ASSERT_DOUBLE_EQ((v1 - v2).x, 2.0);
	ASSERT_DOUBLE_EQ((v1 - v2).y, 2.0);
	ASSERT_DOUBLE_EQ((v1 - v2).z, 2.0);
	ASSERT_DOUBLE_EQ((v1 - v2).length(), 2 * std::sqrt(3.0));
	ASSERT_DOUBLE_EQ((v2 - v1).x, -2.0);
	ASSERT_DOUBLE_EQ((v2 - v1).y, -2.0);
	ASSERT_DOUBLE_EQ((v2 - v1).z, -2.0);
	ASSERT_DOUBLE_EQ((v2 - v1).length(), 2 * std::sqrt(3.0));
	
	Vector3D v4(Point3D(3,0,0), Point3D(3,4,0));
	Vector3D v5(p1, Point3D(3,4,0));
	Vector3D v3 = v5 - v4;		// Calculate the smaller side of 2D-Egyptian triangle
	ASSERT_DOUBLE_EQ(v3.x, 3.0);
	ASSERT_DOUBLE_EQ(v3.y, 0.0);
	ASSERT_DOUBLE_EQ(v3.z, 0.0);

    Vector3D v6 = v1 - v1;
	ASSERT_DOUBLE_EQ(v6.x, 0.0);
	ASSERT_DOUBLE_EQ(v6.y, 0.0);
	ASSERT_DOUBLE_EQ(v6.z, 0.0);
}

//TEST(Vector3D, OperatorUnaryMinus){
//	Point3D p1(0, 0, 0);
//	Point3D p2(1, 1, 1);
//	
//	Vector3D v1(p1, p2);
//	Vector3D v2(p2, p1);
//	// Check current vector coordinates, just for clarity
//	ASSERT_DOUBLE_EQ(v1.x, 1.0);
//	ASSERT_DOUBLE_EQ(v1.y, 1.0);
//	ASSERT_DOUBLE_EQ(v1.z, 1.0);
//	ASSERT_DOUBLE_EQ(v2.x, -1.0);
//	ASSERT_DOUBLE_EQ(v2.y, -1.0);
//	ASSERT_DOUBLE_EQ(v2.z, -1.0);
//	
//	Vector3D v3 = -v1;
//	Vector3D v4 = -v2;
//	ASSERT_DOUBLE_EQ(v3.x, -1.0);
//	ASSERT_DOUBLE_EQ(v3.y, -1.0);
//	ASSERT_DOUBLE_EQ(v3.z, -1.0);
//	ASSERT_DOUBLE_EQ(v4.x, 1.0);
//	ASSERT_DOUBLE_EQ(v4.y, 1.0);
//	ASSERT_DOUBLE_EQ(v4.z, 1.0);
//}
//
//TEST(Vector3D, OperatorMultiplicationOnScalar){
//	Point3D p1(0, 0, 0);
//	Point3D p2(1, 1, 1);
//	
//	Vector3D v1(p1, p2);
//	Vector3D v2(p2, p1);
//	// Check current vector coordinates, just for clarity
//	ASSERT_DOUBLE_EQ(v1.x, 1.0);
//	ASSERT_DOUBLE_EQ(v1.y, 1.0);
//	ASSERT_DOUBLE_EQ(v1.z, 1.0);
//	ASSERT_DOUBLE_EQ(v2.x, -1.0);
//	ASSERT_DOUBLE_EQ(v2.y, -1.0);
//	ASSERT_DOUBLE_EQ(v2.z, -1.0);
//	
//	Vector3D v3 = -v1;
//	Vector3D v4 = -v2;
//	ASSERT_DOUBLE_EQ(v3.x, -1.0);
//	ASSERT_DOUBLE_EQ(v3.y, -1.0);
//	ASSERT_DOUBLE_EQ(v3.z, -1.0);
//	ASSERT_DOUBLE_EQ(v4.x, 1.0);
//	ASSERT_DOUBLE_EQ(v4.y, 1.0);
//	ASSERT_DOUBLE_EQ(v4.z, 1.0);
//}

/*
class Vector3D: public Geometry {
public:

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

    double distanceTo(const Geometry* other) const override {
        const Vector3D* otherVector = dynamic_cast<const Vector3D*>(other);
        if (nullptr == otherVector) {
            return std::numeric_limits<double>::infinity();
        }
        // for shure, I don't know what to return in this case...
        return (Vector3D(x - otherVector->x, y - otherVector->y, z - otherVector->z)).length();
    }

};
*/
