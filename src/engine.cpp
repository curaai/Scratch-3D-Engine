#include "engine.h"
#include "util_vec.h"

#include <iostream>


Engine::Engine()
{

}

Engine::~Engine()
{

}

std::vector<std::pair<triangle, bool>> Engine::draw(Drawable* _mesh, Camera* cam)
{
    const mat44 view_mat = cam->view_matrix();
    const mat44 world_mat = _mesh->world_matrix();
    mat44 transform = proj_mat * view_mat * world_mat;

    auto triangles = _mesh->getConverted(transform);
    auto culled = culling(triangles);

    return culled;
}

std::vector<std::pair<triangle, bool>> Engine::culling(const std::vector<triangle>& triangles)
{
    std::vector<std::pair<triangle, bool>> culled;

    vec3d universal_vec {0, 0, 1};
    for(int i=0; i < triangles.size(); i++) {
        const auto& tri = triangles[i];
        auto norm = tri.surface_normal();
        auto angle = util::vec::dot(norm, universal_vec);
        culled.push_back(std::make_pair(tri, !(angle <= 0)));
    }
    return culled;
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