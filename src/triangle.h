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
};

using Tri3d = triangle<vec3d>;
using IndexedTri3dList = std::vector<std::pair<Tri3d, bool>>;