#include "camera.h"
#include "util_mat.h" 
#include "util_vec.h"

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

void Camera::calcBasis(void)
{
    mat44 viewAngleMat = util::mat::getRotationMat(rotation);
    mat44 posMat = util::mat::getTranslationMat(pos);

    // let camera point forward of cur position
    vec3d direction = viewAngleMat * posMat * vec3d {0, 0, -1};

    vec3d n = util::vec::normalize(pos - direction);
    vec3d u = util::vec::cross(up, n);
    vec3d v = util::vec::cross(n, u);

    viewMat = mat44::identical();
    viewMat.m[0][0] = n.x; viewMat.m[0][1] = n.y; viewMat.m[0][2] = n.z;
    viewMat.m[1][0] = v.x; viewMat.m[1][1] = v.y; viewMat.m[1][2] = v.z;
    viewMat.m[2][0] = n.x; viewMat.m[2][1] = n.y; viewMat.m[2][2] = n.z;
    viewMat.m[0][3] = util::vec::dot(-pos, u);
    viewMat.m[1][3] = util::vec::dot(-pos, v);
    viewMat.m[2][3] = util::vec::dot(-pos, n);
}