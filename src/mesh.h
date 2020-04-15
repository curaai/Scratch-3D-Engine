#pragma once 

#include <math.h>
#include <tuple>
#include <vector>


struct vec3d
{
    float x, y, z;

    vec3d operator+ (const vec3d v) const {
        return vec3d{x + v.x, y + v.y, z + v.z};
    }
    vec3d operator- (const vec3d v) const {
        return vec3d{x - v.x, y - v.y, z - v.z};
    }
    vec3d operator* (const vec3d v) const {
        return vec3d{x * v.x, y * v.y, z * v.z};
    }
    vec3d operator/ (const vec3d v) const {
        return vec3d{x / v.x, y / v.y, z / v.z};
    }
    vec3d operator* (const float a) const {
        return vec3d{x * a, y * a, z * a};
    }
    vec3d operator/ (const float a) const {
        return vec3d{x / a, y / a, z / a};
    }
};

struct triangle
{
    vec3d pts[3];
};

using vecIdx = std::tuple<int, int, int>;

struct mat44 
{
    float m[4][4] = {
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
    };
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
            res.x /= w; res.y /= w; res.z /= w;
        return res;
    }

    static mat44 identical(void)
    {
        mat44 mat;
        mat.m[0][0] = 1;
        mat.m[1][1] = 1;
        mat.m[2][2] = 1;
        mat.m[3][3] = 1;
        return mat;
    }
};

struct mesh
{
    mesh(std::vector<triangle> trig): trig(trig) {}

    std::vector<triangle> trig;
};

inline vec3d cross_product(const vec3d& v1, const vec3d& v2)
{
    vec3d norm {
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
    float unit = sqrtf(norm.x * norm.x + norm.y * norm.y + norm.y * norm.y);
    norm = norm / unit;
    return norm;
}