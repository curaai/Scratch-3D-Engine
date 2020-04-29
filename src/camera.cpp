#include "camera.h"
#include "util_mat.h" 
#include "util_vec.h"

#include <iostream>

Camera::Camera()
{

}

Camera::Camera(vec3d pos) 
    : pos(pos)
{

}

Camera::~Camera()
{

}

const mat44 Camera::view_matrix(void)
{
    mat44 angle_mat = util::mat::getRotationMat(rotation);
    mat44 pos_mat = util::mat::getTranslationMat(pos);

    // let camera point forward of cur position
    vec3d direction = angle_mat * pos_mat * vec3d {0, 0, 1};

    vec3d n = (pos-direction).normalize();
    vec3d u = util::vec::cross(up, n);
    u = u / u.length();
    vec3d v = util::vec::cross(n, u);

    auto view_mat = mat44::identical();
    view_mat.m[0][0] = u.x; view_mat.m[0][1] = u.y; view_mat.m[0][2] = u.z;
    view_mat.m[1][0] = v.x; view_mat.m[1][1] = v.y; view_mat.m[1][2] = v.z;
    view_mat.m[2][0] = n.x; view_mat.m[2][1] = n.y; view_mat.m[2][2] = n.z;
    view_mat.m[0][3] = util::vec::dot(-pos, u);
    view_mat.m[1][3] = util::vec::dot(-pos, v);
    view_mat.m[2][3] = util::vec::dot(-pos, n);

    return view_mat;
}