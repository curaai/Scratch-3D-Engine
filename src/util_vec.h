#pragma once 

#include "vec.h"
#include <cmath>

namespace util {
namespace vec {
    inline vec3d cross(const vec3d a, const vec3d b) {
        return vec3d {a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x};
    }
    inline float dot(const vec3d a, const vec3d b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }
    inline vec3d interpolate(const vec3d& start, const vec3d& end, float alpha) {
        return start + (end - start) * alpha;
    }
    inline vec2d interpolate(const vec2d& start, const vec2d& end, float alpha) {
        return start + (end - start) * alpha;
    }
    inline float interpolate_z(vec3d* pts, vec2d pos) {
        float w[3];
        w[0] = 1 / ((vec2d)pts[0] - pos).length();
        w[1] = 1 / ((vec2d)pts[1] - pos).length();
        w[2] = 1 / ((vec2d)pts[2] - pos).length();
        return (std::abs((float)pts[0].z) * w[0] +
                std::abs((float)pts[1].z) * w[1] +
                std::abs((float)pts[2].z) * w[2]) / (w[0] + w[1] + w[2]);
    }
};
};