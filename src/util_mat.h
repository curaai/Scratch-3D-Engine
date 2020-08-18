#pragma once

#include "mat.h"
#define TO_RADIAN(x) x* M_PI / 180

namespace util {
namespace mat {
inline Mat44 GetRotationMat(vec3d rot)
{
    Mat44 rX = Mat44::identical();
    Mat44 rY = Mat44::identical();
    Mat44 rZ = Mat44::identical();

    rot[0] = TO_RADIAN(rot[0]);
    rot[1] = TO_RADIAN(rot[1]);
    rot[2] = TO_RADIAN(rot[2]);

    // var cos tX, sin tX
    float vcosx = cos(rot[0]);
    float vsinx = sin(rot[0]);
    rX.m[1][1] = vcosx;
    rX.m[1][2] = -vsinx;
    rX.m[2][1] = vsinx;
    rX.m[2][2] = vcosx;

    // var cos tY, sin tY
    float vcosy = cos(rot[1]);
    float vsiny = sin(rot[1]);
    rY.m[0][0] = vcosy;
    rY.m[0][2] = vsiny;
    rY.m[2][0] = -vsiny;
    rY.m[2][2] = vcosy;

    // var cos tZ, sin tZ
    float vcosz = cos(rot[2]);
    float vsinz = sin(rot[2]);
    rZ.m[0][0] = vcosz;
    rZ.m[0][1] = -vsinz;
    rZ.m[1][0] = vsinz;
    rZ.m[1][1] = vcosz;
    return rZ * rY * rX;
}

inline Mat44 GetTranslationMat(const vec3d pos)
{
    auto m = Mat44::identical();
    m.m[0][3] = pos[0];
    m.m[1][3] = pos[1];
    m.m[2][3] = pos[2];
    return m;
}

inline Mat44 GetScaleMat(const vec3d scale)
{
    Mat44 m = Mat44::identical();
    m.m[0][0] *= scale[0];
    m.m[1][1] *= scale[1];
    m.m[2][2] *= scale[2];
    return m;
}
};
};