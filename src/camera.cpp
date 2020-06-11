#include "camera.h"
#include "util_mat.h"
#include "util_vec.h"

#include <iostream>

Camera::Camera(vec3d pos, float aspect_ratio, float fov)
{
    setCameraPos(pos);
    setProjection(aspect_ratio, fov);
}

Camera::~Camera() {}

void Camera::setViewMatrix(void)
{
    Mat44 angle_mat = util::mat::GetRotationMat(rotation);
    Mat44 pos_mat = util::mat::GetTranslationMat(pos);

    // // let camera point forward of cur position
    vec3d direction = angle_mat * pos_mat * vec3d{ 0, 0, 1 };

    vec3d n = (pos - direction).normalize();
    vec3d u = util::vec::Cross(up, n);
    u = u.normalize();
    vec3d v = util::vec::Cross(n, u);

    auto view_mat = Mat44::identical();
    view_mat.m[0][0] = u[0];
    view_mat.m[0][1] = u[1];
    view_mat.m[0][2] = u[2];
    view_mat.m[1][0] = v[0];
    view_mat.m[1][1] = v[1];
    view_mat.m[1][2] = v[2];
    view_mat.m[2][0] = n[0];
    view_mat.m[2][1] = n[1];
    view_mat.m[2][2] = n[2];
    view_mat.m[0][3] = util::vec::Dot(-pos, u);
    view_mat.m[1][3] = util::vec::Dot(-pos, v);
    view_mat.m[2][3] = util::vec::Dot(-pos, n);

    this->view_mat = view_mat;
}

void Camera::setProjection(float aspect_ratio, float fov)
{
    proj_mat = Mat44::identical();

    // convert degree to radian
    float fovRad = 1.0f / tanf((fov / 180.0f * M_PI) * 0.5f);

    proj_mat.m[0][0] = aspect_ratio * fovRad;
    proj_mat.m[1][1] = fovRad;
    proj_mat.m[2][2] = -proj_far / (proj_far - proj_near);
    proj_mat.m[2][3] = -(proj_far * proj_near) / (proj_far - proj_near);
    proj_mat.m[3][2] = -1.0f;
    proj_mat.m[3][3] = 0.0f;
}