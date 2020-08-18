#pragma once

#include "Fragment.h"
#include "VertexShader.h"
#include "window.h"

class Rasterizer
{
public:
    static std::vector<Fragment> rasterize(const Window* win,
                                           std::vector<VSTriangle>& vst_list)
    {
        std::vector<Fragment> res;

        auto screen_mat = win->screenMatrix();
        for (const auto& vst : vst_list) {
            RSOutput rso0{ vst[0] };
            RSOutput rso1{ vst[1] };
            RSOutput rso2{ vst[2] };

            rso0.spos = screen_mat * vst[0].cpos;
            rso1.spos = screen_mat * vst[1].cpos;
            rso2.spos = screen_mat * vst[2].cpos;

            bool is_culled = culling(vst.cposTriangle());

            res.push_back(
                Fragment{ rso0, rso1, rso2, vst.tangent_light_tri, is_culled });
        }
        return res;
    }

private:
    static bool culling(Tri3d clipped_tri)
    {
        // change to ccw order for clip space
        std::swap(clipped_tri[2], clipped_tri[0]);
        auto normal = util::tri::SurfaceNormal(clipped_tri);
        auto angle = util::vec::Dot(normal, vec3d{ 0, 0, 1 });
        return angle >= 0;
    }
};