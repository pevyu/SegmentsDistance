    // Geometry.h
    #ifndef GEOMETRY_H
    #define GEOMETRY_H

    #include <cmath>

    class Geometry {
    public:
        virtual ~Geometry() = default;
        virtual double distanceTo(const Geometry* other) const = 0;
        //virtual Geometry* clone() const = 0; do not need right now
        static constexpr double EPSILON = 1e-9;
    };

    #endif