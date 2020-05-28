#pragma once

#include "mesh.h"
#include "tex_vertex.h"
#include "zbuffer.h"

struct pos
{
    pos(float x, float y)
        : x(static_cast<int>(x))
        , y(static_cast<int>(y))
    {}
    pos(int x, int y)
        : x(x)
        , y(y)
    {}
    int x;
    int y;
};

struct line
{
    pos a;
    pos b;
};

namespace util {
namespace draw {
inline SDL_Color get_pixel(const SDL_Surface* const surface,
                           const uint x,
                           const uint y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    uint8_t* p = (uint8_t*)surface->pixels + y * surface->pitch + x * bpp;
    uint32_t _pixel;
    switch (bpp) {
        case 1:
            _pixel = static_cast<uint32_t>(*p);
            break;
        case 2:
            _pixel = static_cast<uint32_t>(*(uint16_t*)p);
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                _pixel = p[0] << 16 | p[1] << 8 | p[2];
            else
                _pixel = p[0] | p[1] << 8 | p[2] << 16;
            break;
        case 4:
            _pixel = static_cast<uint32_t>(*(uint32_t*)p);
            break;
        default:
            return SDL_Color();
    }
    SDL_Color rgb;
    SDL_GetRGB(_pixel, surface->format, &rgb.r, &rgb.g, &rgb.b);
    rgb.a = 255;
    return rgb;
}

inline void draw_flat_triangle_texture(const TexVertex& v0,
                                       const TexVertex& v1,
                                       const TexVertex& v2,
                                       const TexVertex& dv1,
                                       const TexVertex& dv2,
                                       TexVertex& e2,
                                       const SDL_Surface* const texture,
                                       ZBuffer* zbuf)
{
    TexVertex e1 = v0;
    const int y_start = (int)ceil(v0.pos[1] - 0.5f);
    const int y_end = (int)ceil(v2.pos[1] - 0.5f);

    e1 += dv1 * (float(y_start) + 0.5f - v0.pos[1]);
    e2 += dv2 * (float(y_start) + 0.5f - v0.pos[1]);

    const float tex_width = texture->w;
    const float tex_height = texture->h;
    const float tex_clamp_x = tex_width - 1.0f;
    const float tex_clamp_y = tex_height - 1.0f;

    for (int y = y_start; y < y_end; y++, e1 += dv1, e2 += dv2) {
        const int x_start = (int)ceil(e1.pos[0] - 0.5f);
        const int x_end = (int)ceil(e2.pos[0] - 0.5f);

        const vec2d delta_line =
            (e2.texel - e1.texel) / (e2.pos[0] - e1.pos[0]);

        vec2d init_line =
            e1.texel + delta_line * (float(x_start) + 0.5 - e1.pos[0]);
        for (int x = x_start; x < x_end; x++, init_line += delta_line) {
            // put pixel (x, y)
            // get pixel
            auto b = std::fmod(init_line[1] * tex_height, tex_clamp_y);
            auto pixel = get_pixel(
                texture,
                int(std::fmod(init_line[0] * tex_width, tex_clamp_x)),
                int(std::fmod(init_line[1] * tex_height, tex_clamp_y)));
            // auto z = util::vec::interpolate_z(global_t->pts,
            //                                   vec2d{ (float)x, (float)y });
            // zbuf->put_pixel(vec3d{ x, y, z }, pixel);
        }
    }
}
inline void draw_flat_top_triangle_texture(const TexVertex& v0,
                                           const TexVertex& v1,
                                           const TexVertex& v2,
                                           const SDL_Surface* const texture,
                                           ZBuffer* zbuf)
{
    const float delta_y = v2.pos[1] - v0.pos[1];
    const auto d1 = (v2 - v0) / delta_y;
    const auto d2 = (v2 - v1) / delta_y;
    TexVertex edge(v1);

    draw_flat_triangle_texture(v0, v1, v2, d1, d2, edge, texture, zbuf);
}
inline void draw_flat_bottom_triangle_texture(const TexVertex& v0,
                                              const TexVertex& v1,
                                              const TexVertex& v2,
                                              const SDL_Surface* const texture,
                                              ZBuffer* zbuf)
{
    const float delta_y = v2.pos[1] - v0.pos[1];
    const auto d1 = (v1 - v0) / delta_y;
    const auto d2 = (v2 - v0) / delta_y;
    TexVertex edge(v0);

    draw_flat_triangle_texture(v0, v1, v2, d1, d2, edge, texture, zbuf);
}
inline void draw_triangle_texture(triangle<TexVertex> tv_tri,
                                  const SDL_Surface* const texture,
                                  ZBuffer* zbuf)
{
    // global_t = &pos_tri;

    TexVertex& v0 = tv_tri[0];
    TexVertex& v1 = tv_tri[1];
    TexVertex& v2 = tv_tri[2];

    if (v1.pos[1] < v0.pos[1])
        std::swap(v0, v1);
    if (v2.pos[1] < v1.pos[1])
        std::swap(v1, v2);
    if (v1.pos[1] < v0.pos[1])
        std::swap(v0, v1);

    if (v0.pos[1] == v1.pos[1]) // natural flat-top triangle
    {
        if (v1.pos[0] < v0.pos[0])
            std::swap(v0, v1);
        draw_flat_top_triangle_texture(v0, v1, v2, texture, zbuf);
    } else if (v1.pos[1] == v2.pos[1]) // natural flat-bottom triangle
    {
        if (v2.pos[0] < v1.pos[0])
            std::swap(v1, v2);
        draw_flat_bottom_triangle_texture(v0, v1, v2, texture, zbuf);
    } else // genera
    {
        // split
        const float split = (v1.pos[1] - v0.pos[1]) / (v2.pos[1] - v0.pos[1]);

        const TexVertex v3(
            util::vec::interpolate<vec3d>(v0.pos, v2.pos, split),
            util::vec::interpolate<vec2d>(v0.texel, v2.texel, split));
        if (v1.pos[0] < v3.pos[0]) {
            draw_flat_bottom_triangle_texture(v0, v1, v3, texture, zbuf);
            draw_flat_top_triangle_texture(v1, v3, v2, texture, zbuf);
        } else {
            draw_flat_bottom_triangle_texture(v0, v3, v1, texture, zbuf);
            draw_flat_top_triangle_texture(v3, v1, v2, texture, zbuf);
        }
    }
    // global_t = nullptr;
}

}; // namespace draw
}; // namespace util