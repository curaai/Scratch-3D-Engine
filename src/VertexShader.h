#pragma once

#include "Drawable.h"
#include "camera.h"

class VertexShader
{
public:
    static std::vector<VSTriangle> vertexing(const Drawable* obj,
                                             const Camera* cam)
    {
        auto obj_rotate_mat = obj->getRotateMatrix();
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
            triangle<vec3d> norm_tri{ obj_rotate_mat * tri.pts[0].wnormal,
                                      obj_rotate_mat * tri.pts[1].wnormal,
                                      obj_rotate_mat * tri.pts[2].wnormal };

            VSTriangle fvt{
                tri.wposTriangle(), norm_tri, tri.tposTriangle(), clipped_tri
            };
            res.push_back(fvt);
        }
        return res;
    }
};