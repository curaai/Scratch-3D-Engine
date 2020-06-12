#pragma once

#include "Mesh.h"
#include "mat.h"

class Camera
{
public:
    explicit Camera(vec3d pos, float aspect_ratio, float fov);
    ~Camera();

    const Mat44& viewMatrix(void) const { return view_mat; };
    const Mat44& projectionMatrix(void) const { return proj_mat; };

    void setCameraPos(const vec3d& v)
    {
        pos = v;
        setViewMatrix();
    }
    void setCameraRotation(const vec3d& v)
    {
        rotation = v;
        setViewMatrix();
    }
    void setProjection(float aspect_ratio, float fov);

public:
    // Camera Components
    vec3d pos;
    vec3d rotation{ 0, 0, 0 };

private:
    void setViewMatrix(void);

private:
    vec3d at;
    vec3d up{ 0, 1, 0 };
    Mat44 view_mat;

    // projection components
    Mat44 proj_mat;
    float aspect_ratio;
    float fov;
    const float proj_far = 1000.0f;
    const float proj_near = 0.5f;
};