// vec3.h - 3D vector class for ray tracing
// Provides a 3D vector with common operations and utility functions
#ifndef VEC3_H
#define VEC3_H

#include <cmath>    // For mathematical functions like sqrt
#include <iostream> // For output streaming

// The vec3 class represents a 3D vector or point in space
class vec3
{
public:
    double e[3]; // The vector components: e[0]=x, e[1]=y, e[2]=z

    // Default constructor initializes vector to (0,0,0)
    vec3() : e{0, 0, 0} {}
    // Construct a vector with given x, y, z components
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    // Accessor for x component
    double x() const { return e[0]; }
    // Accessor for y component
    double y() const { return e[1]; }
    // Accessor for z component
    double z() const { return e[2]; }

    // Unary minus: returns the negation of the vector
    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    // Const subscript operator: get component by index
    double operator[](int i) const { return e[i]; }
    // Non-const subscript operator: get/set component by index
    double &operator[](int i) { return e[i]; }

    // Compound addition: add another vector to this one
    vec3 &operator+=(const vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    // Compound multiplication: scale this vector by a scalar
    vec3 &operator*=(double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    // Compound division: divide this vector by a scalar
    vec3 &operator/=(double t)
    {
        return *this *= 1 / t;
    }

    // Compute the Euclidean length (magnitude) of the vector
    double length() const
    {
        return std::sqrt(length_squared());
    }

    // Compute the squared length (avoids sqrt for efficiency)
    double length_squared() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }
};

// Alias for vec3 to represent a 3D point (for clarity in code)
using point3 = vec3;

// Output stream operator: print vector components to output stream
inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Vector addition: add two vectors component-wise
inline vec3 operator+(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// Vector subtraction: subtract two vectors component-wise
inline vec3 operator-(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// Component-wise vector multiplication
inline vec3 operator*(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// Scalar multiplication: scale vector by a scalar (scalar * vector)
inline vec3 operator*(double t, const vec3 &v)
{
    return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

// Scalar multiplication: scale vector by a scalar (vector * scalar)
inline vec3 operator*(const vec3 &v, double t)
{
    return t * v;
}

// Scalar division: divide vector by a scalar
inline vec3 operator/(const vec3 &v, double t)
{
    return (1 / t) * v;
}

// Dot product: returns the scalar product of two vectors
inline double dot(const vec3 &u, const vec3 &v)
{
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// Cross product: returns the vector perpendicular to u and v
inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

// Returns the unit vector (normalized vector) in the same direction as v
inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

#endif