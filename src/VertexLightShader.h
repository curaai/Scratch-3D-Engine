#pragma once

#include "camera.h"
#include "light.h"

#include "util_vec.h"

class LightShader
{
    // Follow Phong Lighting Model
    std::vector<vec3d> shading(const IndexTri3dList& triangles,
                               Light* src_light,
                               Camera* cam)
    {
        using namespace util::tri;
        using namespace util::vec;
        std::vector<vec3d> lights;
        for (const auto& indexed : triangles) {
            if (!indexed.second)
                continue;

            // Essential parameter
            const auto& tri = indexed.first;
            const vec3d tri_normal = SurfaceNormal(tri);
            const vec3d light_color = src_light->lightColor();
            // center point of triangle
            const vec3d tri_pos{
                (tri[0][0] + tri[1][0] + tri[2][0]) / 3,
                (tri[0][1] + tri[1][1] + tri[2][1]) / 3,
                (tri[0][2] + tri[1][2] + tri[2][2]) / 3,
            };
            const vec3d light_direction = src_light->pos - tri_pos;

            // Diffuse Relfection
            const vec3d pD =
                std::max(Dot(light_direction, tri_normal), 0.0f) * light_color;
            // Specular Reflection
            const vec3d sRefl =
                2.0f * tri_normal * Dot(light_direction, light_direction) -
                light_direction;
            const vec3d sView = (cam->pos - tri_pos).normalize();
            float specular =
                std::max(std::pow(std::max(Dot(sRefl, sView), 0.0f), 5), 0.0f);
            const vec3d pS = specular * light_color;
            // Ambient Reflection
            // Skip
            // Emissive Reflection
            // Skip

            lights.push_back(pD + pS);
        }

        return lights;
    }
};