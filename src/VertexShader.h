#pragma once

#include "Drawable.h"
#include "camera.h"

class VertexShader
{
public:
    static std::vector<VSTriangle> vertexing(const Drawable* obj,
                                             const Camera* cam)
    {
        auto world_mat = obj->worldMatrix();
        auto view_mat = cam->viewMatrix();
        auto proj_mat = cam->projectionMatrix();
        Mat44 transform = proj_mat * view_mat * world_mat;

        std::vector<VSTriangle> res;
        for (const auto& tri : obj->mesh.triangles()) {
            triangle<vec3d> clipped_tri{
                transform * tri.pts[0].wpos,
                transform * tri.pts[1].wpos,
                transform * tri.pts[2].wpos,
            };
            VSTriangle fvt{ tri.wposTriangle(),
                            tri.wnormalTriangle(),
                            tri.tposTriangle(),
                            clipped_tri };
            res.push_back(fvt);
        }
        return res;
    }
};