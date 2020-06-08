#pragma once

#include "vec.h"

template<typename T>
struct triangle
{
    T pts[3];

    bool operator==(const triangle<T>& t)
    {
        bool flag = true;
        for (int i = 0; i < 3; i++)
            flag &= t.pts[i] == pts[i];
        return flag;
    }
    T& operator[](const int idx) { return pts[idx]; }
    T operator[](const int idx) const { return pts[idx]; }
};

using Tri3d = triangle<vec3d>;
using Tri2d = triangle<vec2d>;