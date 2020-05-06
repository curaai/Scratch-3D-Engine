#pragma once 

#include "vec.h"

namespace util {
namespace vec {
    inline vec3d cross(const vec3d a, const vec3d b) {
        return vec3d {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
    }
    inline float dot(const vec3d a, const vec3d b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
};
};