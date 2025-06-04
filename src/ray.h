#ifndef RAY_H
#define RAY_H

#include "vec3.h" // For vec3 class representing 3D vectors

class ray {

public:
    ray() {}
    ray(const point3& origin, const vec3& direction)
        : orig(origin), dir(direction) {
    }

    const point3& origin() const { return orig; } // Get the ray's origin
    const vec3& direction() const { return dir; } // Get the ray's direction

    point3 at(double t) const {
        return orig + t * dir;
    }

private:
    point3 orig; // The starting point of the ray
    vec3 dir;    // The direction vector of the ray
};

#endif