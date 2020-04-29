#include "engine.h"
#include <iostream>

Engine::Engine()
{

}

Engine::~Engine()
{

}

std::vector<triangle> Engine::draw(Drawable* _mesh, Camera* cam)
{
    const mat44 view_mat = cam->view_matrix();
    const mat44 world_mat = _mesh->world_matrix();
    mat44 transform = world_mat * view_mat * proj_mat;

    // using namespace std;
    // cout << "== View Matrix == " << endl;
    // cout << view_mat << endl;

    // cout << "== World Matrix == " << endl;
    // cout << world_mat << endl;

    // cout << "== Projection Matrix == " << endl;
    // cout << proj_mat << endl;

    // cout << "== Final Matrix == " << endl;
    // cout << transform << endl;

    return _mesh->getConverted(transform);
}

void Engine::set_projection(float aspect_ratio, float fov, float near, float far)
{
    proj_mat = mat44::identical();

    // convert degree to radian  
    float fovRad = 1.0f / tanf((fov / 180.0f * M_PI) * 0.5f);

    proj_mat.m[0][0] = aspect_ratio * fovRad;
    proj_mat.m[1][1] = fovRad;
    proj_mat.m[2][2] = far / (far - near);
    proj_mat.m[2][3] = (far * near) / (far - near);
    proj_mat.m[3][2] = -1.0f;
    proj_mat.m[3][3] = 0.0f;
}