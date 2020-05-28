#pragma once

#include "vec.h"
#include <cmath>

namespace util {
namespace vec {
inline vec3d cross(const vec3d a, const vec3d b)
{
    return vec3d{ { a[1] * b[2] - a[2] * b[1],
                    a[2] * b[0] - a[0] * b[2],
                    a[0] * b[1] - a[1] * b[0] } };
}
inline float dot(const vec3d a, const vec3d b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
template<typename T>
inline T interpolate(const T& start, const T& end, float alpha)
{
    return start + (end - start) * alpha;
}
inline float interpolate_z(vec3d* pts, vec2d pos)
{
    float w[3];
    w[0] = 1 / ((vec2d)pts[0] - pos).length();
    w[1] = 1 / ((vec2d)pts[1] - pos).length();
    w[2] = 1 / ((vec2d)pts[2] - pos).length();
    return (std::abs((float)pts[0][2]) * w[0] +
            std::abs((float)pts[1][2]) * w[1] +
            std::abs((float)pts[2][2]) * w[2]) /
           (w[0] + w[1] + w[2]);
}
};
namespace tri {
inline vec3d surface_normal(const Tri3d& tri)
{
    auto a = tri.pts[1] - tri.pts[0];
    auto b = tri.pts[2] - tri.pts[0];
    return vec3d{ a[1] * b[2] - a[2] * b[1],
                  a[2] * b[0] - a[0] * b[2],
                  a[0] * b[1] - a[1] * b[0] };
}
};
};