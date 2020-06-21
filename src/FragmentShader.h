#pragma once

#include "Fragment.h"
#include "Texture.h"
#include "camera.h"
#include "light.h"

class FragmentShader
{
public:
    FragmentShader(Light* light, Camera* cam)
        : light(light)
        , cam(cam)
    {}

    std::vector<Fragment> lighting(const std::vector<Fragment>& fragments,
                                   const Texture* rsc)
    {
        using namespace util::tri;
        using namespace util::vec;

        std::vector<Fragment> lighted;

        const vec3d light_color = light->lightColor();
        for (const auto& fragment : fragments) {
            if (fragment.is_culled)
                continue;

            Fragment _fragment{ fragment };
            for (auto& fraxel : _fragment.fraxels) {
                fraxel.wnormal = fraxel.wnormal.normalize();
                SDL_Color c = rsc->pixel(fraxel.texel[0], fraxel.texel[1]);
                vec3d _c{ c.r / 255.f, c.g / 255.f, c.b / 255.f };

                const vec3d light_direction =
                    (light->pos - fraxel.wpos).normalize();

                // Diffuse Relfection
                const vec3d pD =
                    light_color *
                    std::max(Dot(light_direction, fraxel.wnormal), 0.0f);
                // Specular Reflection
                const vec3d sRefl = fraxel.wnormal * 2.0f *
                                        Dot(fraxel.wnormal, light_direction) -
                                    light_direction;
                const vec3d sView = (cam->pos - fraxel.wpos).normalize();
                float specular = std::max(
                    std::pow(std::max(Dot(sRefl, sView), 0.0f), 5), 0.0);
                const vec3d pS = light_color * specular;
                const vec3d pA{ 0.1f, 0.1f, 0.1f };

                vec3d color = pD * _c + pS * _c + pA * _c;
                color.clamp();
                color *= 255;
                fraxel.color = SDL_Color{ static_cast<uint8_t>(color[0]),
                                          static_cast<uint8_t>(color[1]),
                                          static_cast<uint8_t>(color[2]),
                                          c.a };
            }
            lighted.push_back(_fragment);
        }
        return lighted;
    }

private:
    Light* light;
    Camera* cam;
};