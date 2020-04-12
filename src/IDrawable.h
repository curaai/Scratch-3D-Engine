#pragma once 

#include <tuple>
#include <vector>

struct vec3d
{
    float x, y, z;
};

struct mat44 
{
    float m[4][4] = {0};
    mat44 operator* (const mat44& mat)
    {
        mat44 res;
        for(int i=0; i<4; i++) {
            for(int j=0; j<4; j++) {
                for(int k=0; k<4; k++) {
                    res.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }
        return res;
    }
    vec3d operator* (const vec3d& vec)
    {
        vec3d res;
        res.x = vec.x * m[0][0] + vec.y * m[1][0] + vec.z * m[2][0] + m[3][0];
        res.y = vec.x * m[0][1] + vec.y * m[1][1] + vec.z * m[2][1] + m[3][1];
        res.z = vec.x * m[0][2] + vec.y * m[1][2] + vec.z * m[2][2] + m[3][2];
        float w = vec.x * m[0][3] + vec.y * m[1][3] + vec.z * m[2][3] + m[3][3];
        if(w != 0.0f)
            res.x /= w; res.y /= w; res.z /= z;
        return res;
    }
};

struct triangle
{
    vec3d trig[3];
};

using vecIdx = std::tuple<int, int, int>;
struct mesh
{
    mesh(std::vector<vec3d> pts, std::vector<vecIdx> indices)
    {
        for(auto idx : indices) {
            trig.push_back(triangle {pts[std::get<0>(idx)], pts[std::get<1>(idx)], pts[std::get<2>(idx)]});
        }
    }

    std::vector<triangle> trig;
};
