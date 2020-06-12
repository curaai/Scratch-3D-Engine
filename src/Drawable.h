#pragma once

#include "Mesh.h"
#include "resource.h"
#include "util_mat.h"

#include <math.h>

class Drawable
{
public:
    Drawable(const Mesh& mesh, const Resource& rsc)
        : mesh(mesh)
        , resource(rsc)
    {
        rotate_mat = Mat44::identical();
        translate_mat = Mat44::identical();
        scale_mat = Mat44::identical();
    }
    ~Drawable() {}

    Mat44 worldMatrix(void) const
    {
        return translate_mat * scale_mat * rotate_mat;
    }

    void setTranslate(const vec3d v)
    {
        this->pos = v;
        translate_mat = util::mat::GetTranslationMat(v);
    }
    void setScale(const vec3d v)
    {
        this->scale = v;
        scale_mat = util::mat::GetScaleMat(v);
    }
    void setRotate(const vec3d v)
    {
        this->rotation = v;
        rotate_mat = util::mat::GetRotationMat(v);
    }
    Mat44 getTranslateMatrix(void) const { return translate_mat; }
    Mat44 getRotateMatrix(void) const { return rotate_mat; }
    Mat44 getScaleMatrix(void) const { return scale_mat; }

public:
    const Mesh mesh;
    const Resource resource;
    vec3d pos;
    vec3d rotation;
    vec3d scale;

protected:
    Mat44 translate_mat, scale_mat, rotate_mat;
};