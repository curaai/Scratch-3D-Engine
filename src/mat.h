#pragma once

#include "vec.h"

struct Mat44
{
    Mat44() {}
    Mat44(const vec3d& a, const vec3d& b, const vec3d& c, const vec3d& d)
    {
        m[0][0] = a[0];
        m[1][0] = a[1];
        m[2][0] = a[2];
        m[0][1] = b[0];
        m[1][1] = b[1];
        m[2][1] = b[2];
        m[0][2] = c[0];
        m[1][2] = c[1];
        m[2][2] = c[2];
        m[0][3] = d[0];
        m[1][3] = d[1];
        m[2][3] = d[2];
    }

    float m[4][4] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    };
    Mat44 operator*(const Mat44& mat) const
    {
        Mat44 res;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < 4; k++) {
                    res.m[i][j] += m[i][k] * mat.m[k][j];
                }
            }
        }
        return res;
    }
    vec3d operator*(const vec3d& vec) const
    {
        vec3d res;
        res[0] =
            vec[0] * m[0][0] + vec[1] * m[0][1] + vec[2] * m[0][2] + m[0][3];
        res[1] =
            vec[0] * m[1][0] + vec[1] * m[1][1] + vec[2] * m[1][2] + m[1][3];
        res[2] =
            vec[0] * m[2][0] + vec[1] * m[2][1] + vec[2] * m[2][2] + m[2][3];
        float w =
            vec[0] * m[3][0] + vec[1] * m[3][1] + vec[2] * m[3][2] + m[3][3];
        if (w != 0.0f)
            res[0] /= w;
        res[1] /= w;
        res[2] /= w;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const Mat44& mat)
    {
        os << mat.m[0][0] << ' ' << mat.m[0][1] << ' ' << mat.m[0][2] << ' '
           << mat.m[0][3] << std::endl;
        os << mat.m[1][0] << ' ' << mat.m[1][1] << ' ' << mat.m[1][2] << ' '
           << mat.m[1][3] << std::endl;
        os << mat.m[2][0] << ' ' << mat.m[2][1] << ' ' << mat.m[2][2] << ' '
           << mat.m[2][3] << std::endl;
        os << mat.m[3][0] << ' ' << mat.m[3][1] << ' ' << mat.m[3][2] << ' '
           << mat.m[3][3] << std::endl;
        return os;
    }

    static Mat44 identical(void)
    {
        Mat44 mat;
        mat.m[0][0] = 1;
        mat.m[1][1] = 1;
        mat.m[2][2] = 1;
        mat.m[3][3] = 1;
        return mat;
    }
};