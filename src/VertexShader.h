#pragma once

#include "Drawable.h"
#include "camera.h"

class VSTriangle : public triangle<VSOutput>
{
public:
    // for tangent-space normal mapping
    // convert light to tangent-space light with TBL
    triangle<vec3d> tangent_light_tri{};

    VSTriangle(const triangle<vec3d>& world_tri,
               const triangle<vec3d>& wnormal_tri,
               const triangle<vec2d>& tpos_tri,
               const triangle<vec3d>& clipped_tri)
    {
        pts[0].cpos = clipped_tri[0];
        pts[1].cpos = clipped_tri[1];
        pts[2].cpos = clipped_tri[2];

        pts[0].wpos = world_tri[0];
        pts[1].wpos = world_tri[1];
        pts[2].wpos = world_tri[2];

        pts[0].wnormal = wnormal_tri[0];
        pts[1].wnormal = wnormal_tri[1];
        pts[2].wnormal = wnormal_tri[2];

        pts[0].tpos = tpos_tri[0];
        pts[1].tpos = tpos_tri[1];
        pts[2].tpos = tpos_tri[2];
    }

    void initTangentLight(const Light& light)
    {
        using namespace util::vec;
        const auto edge1 = pts[1].wpos - pts[0].wpos;
        const auto edge2 = pts[2].wpos - pts[0].wpos;
        const auto dUV1 = pts[1].tpos - pts[0].tpos;
        const auto dUV2 = pts[2].tpos - pts[0].tpos;

        // inverse tangent constatnt
        float inv_t = 1.0f / (dUV1[0] * dUV2[1] - dUV2[0] * dUV1[1]);

        vec3d t = ((edge1 * dUV2[1] - edge2 * dUV1[1]) * inv_t).normalize();
        vec3d b = ((edge1 * -dUV2[0] + edge2 * dUV1[0]) * inv_t).normalize();
        for (int i = 0; i < 2; i++) {
            const vec3d n = pts[i].wnormal;

            // const vec3d t_inv = t - n * Dot(n, t);
            // const vec3d b_inv = b - n * Dot(n, t) - t_inv * Dot(t_inv, b);
            const vec3d t_inv = t;
            const vec3d b_inv = b;

            Mat44 TBL = Mat44::identical();
            TBL.m[0][0] = t_inv[0];
            TBL.m[0][1] = t_inv[1];
            TBL.m[0][2] = t_inv[2];
            TBL.m[1][0] = b_inv[0];
            TBL.m[1][1] = b_inv[1];
            TBL.m[1][2] = b_inv[2];
            TBL.m[2][0] = n[0];
            TBL.m[2][1] = n[1];
            TBL.m[2][2] = n[2];

            tangent_light_tri[i] =
                (TBL * (light.pos - pts[i].wpos)).normalize();
        }
    }

    Tri3d cposTriangle(void) const
    {
        return Tri3d{ pts[0].cpos, pts[1].cpos, pts[2].cpos };
    }
    Tri3d wposTriangle(void) const
    {
        return Tri3d{ pts[0].wpos, pts[1].wpos, pts[2].wpos };
    }
    Tri3d wnormalTriangle(void) const
    {
        return Tri3d{ pts[0].wnormal, pts[1].wnormal, pts[2].wnormal };
    }
    Tri2d tposTriangle(void) const
    {
        return Tri2d{ pts[0].tpos, pts[1].tpos, pts[2].tpos };
    }
};

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