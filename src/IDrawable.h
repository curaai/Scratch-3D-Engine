#pragma once

#include "mesh.h"
#include "resource.h"
#include "util_mat.h"
#include "util_std.h"

#include <math.h>

class Drawable
{
public:
    Drawable(const mesh& mesh_, const Resource& rsc)
        : mesh_(mesh_)
        , rsc(rsc)
    {
        rotateMat = mat44::identical();
        translateMat = mat44::identical();
        scaleMat = mat44::identical();
    }
    ~Drawable() {}

    std::vector<Tri3d> getConverted(const mat44& mat)
    {
        std::vector<Tri3d> cvtTris;
        for (auto tri : mesh_.triangles()) {
            Tri3d newTri;
            newTri.pts[0] = mat * tri.pts[0];
            newTri.pts[1] = mat * tri.pts[1];
            newTri.pts[2] = mat * tri.pts[2];
            cvtTris.push_back(newTri);
        }
        return cvtTris;
    }

    const mat44 world_matrix(void)
    {
        return translateMat * scaleMat * rotateMat;
    }

    void setTranslate(float x, float y, float z)
    {
        translateMat = util::mat::getTranslationMat(vec3d{ x, y, z });
    }
    void setScale(float x, float y, float z)
    {
        scaleMat = util::mat::getScaleMat(vec3d{ x, y, z });
    }
    void setRotate(float x, float y, float z)
    {
        rotateMat = util::mat::getRotationMat(vec3d{ x, y, z });
    }

public:
    const mesh mesh_;
    const Resource rsc;

private:
    mat44 translateMat, scaleMat, rotateMat;
};