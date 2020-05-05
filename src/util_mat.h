#include "mesh.h"

namespace util {
namespace mat { 
    inline mat44 getRotationMat(vec3d rot) {
        mat44 rX = mat44::identical();
        mat44 rY = mat44::identical();
        mat44 rZ = mat44::identical();

        rot.x = TO_RADIAN(rot.x);
        rot.y = TO_RADIAN(rot.y);
        rot.z = TO_RADIAN(rot.z);

        // var cos tX, sin tX
        float vcosx = cos(rot.x); float vsinx = sin(rot.x);
        rX.m[1][1] = vcosx;
        rX.m[1][2] = -vsinx;
        rX.m[2][1] = vsinx;
        rX.m[2][2] = vcosx;

        // var cos tY, sin tY
        float vcosy = cos(rot.y); float vsiny = sin(rot.y);
        rY.m[0][0] = vcosy;
        rY.m[0][2] = vsiny;
        rY.m[2][0] = -vsiny;
        rY.m[2][2] = vcosy;

        // var cos tZ, sin tZ
        float vcosz = cos(rot.z); float vsinz = sin(rot.z);
        rZ.m[0][0] = vcosz;
        rZ.m[0][1] = -vsinz;
        rZ.m[1][0] = vsinz;
        rZ.m[1][1] = vcosz;
        return rZ * rY * rX;
    }

    inline mat44 getTranslationMat(const vec3d pos) {
        auto m = mat44::identical();
        m.m[0][3] = pos.x;
        m.m[1][3] = pos.y;
        m.m[2][3] = pos.z;
        return m;
    }

    inline mat44 getScaleMat(const vec3d scale) {
        mat44 m = mat44::identical();
        m.m[0][0] *= scale.x;
        m.m[1][1] *= scale.y;
        m.m[2][2] *= scale.z;
        return m;
    }
};
};