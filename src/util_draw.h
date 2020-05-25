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
triangle* global_t = nullptr;
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

namespace {
inline void fill_bottom_flat_triangle(pos v1,
                                      pos v2,
                                      pos v3,
                                      std::vector<line>& lines)
{
    float invslope1 = (float)(v2.x - v1.x) / (v2.y - v1.y);
    float invslope2 = (float)(v3.x - v1.x) / (v3.y - v1.y);

    float curx1 = v1.x;
    float curx2 = v1.x;

    for (int scanlineY = v1.y; scanlineY <= v2.y; scanlineY++) {
        auto _min = std::min(static_cast<int>(curx1), static_cast<int>(curx2));
        auto _max = std::max(static_cast<int>(curx1), static_cast<int>(curx2));
        lines.push_back(line{ pos{ _min, scanlineY }, pos{ _max, scanlineY } });
        curx1 += invslope1;
        curx2 += invslope2;
    }
}

inline void fill_top_flat_triangle(pos v1,
                                   pos v2,
                                   pos v3,
                                   std::vector<line>& lines)
{
    float invslope1 = (float)(v3.x - v1.x) / (v3.y - v1.y);
    float invslope2 = (float)(v3.x - v2.x) / (v3.y - v2.y);

    float curx1 = v3.x;
    float curx2 = v3.x;

    for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--) {
        auto _min = std::min(static_cast<int>(curx1), static_cast<int>(curx2));
        auto _max = std::max(static_cast<int>(curx1), static_cast<int>(curx2));
        lines.push_back(line{ pos{ _min, scanlineY }, pos{ _max, scanlineY } });
        curx1 -= invslope1;
        curx2 -= invslope2;
    }
}
} // namespace

inline std::vector<line> triangle_indices(const triangle& t)
{
    std::vector<line> lines;
    pos v1{ t.pts[0].x, t.pts[0].y };
    pos v2{ t.pts[1].x, t.pts[1].y };
    pos v3{ t.pts[2].x, t.pts[2].y };

    /* at first sort the three vertices by y-coordinate ascending so v1 is the
     * topmost vertice */
    if (v2.y < v1.y)
        std::swap(v2, v1);
    if (v3.y < v1.y)
        std::swap(v3, v1);
    if (v3.y < v2.y)
        std::swap(v3, v2);

    /* here we know that v1.y <= v2.y <= v3.y */
    /* check for trivial case of bottom-flat triangle */
    if (v2.y == v3.y) {
        fill_bottom_flat_triangle(v1, v2, v3, lines);
    }
    /* check for trivial case of top-flat triangle */
    else if (v1.y == v2.y) {
        fill_top_flat_triangle(v1, v2, v3, lines);
    } else {
        /* general case - split the triangle in a topflat and bottom-flat one */
        pos v4{ static_cast<int>(v1.x + ((v2.y - v1.y) / (float)(v3.y - v1.y)) *
                                            (v3.x - v1.x)),
                static_cast<int>(v2.y) };
        fill_bottom_flat_triangle(v1, v2, v4, lines);
        fill_top_flat_triangle(v2, v4, v3, lines);
    }
    return lines;
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
    const int y_start = (int)ceil(v0.pos.y - 0.5f);
    const int y_end = (int)ceil(v2.pos.y - 0.5f);

    e1 += dv1 * (float(y_start) + 0.5f - v0.pos.y);
    e2 += dv2 * (float(y_start) + 0.5f - v0.pos.y);

    const float tex_width = texture->w;
    const float tex_height = texture->h;
    const float tex_clamp_x = tex_width - 1.0f;
    const float tex_clamp_y = tex_height - 1.0f;

    for (int y = y_start; y < y_end; y++, e1 += dv1, e2 += dv2) {
        const int x_start = (int)ceil(e1.pos.x - 0.5f);
        const int x_end = (int)ceil(e2.pos.x - 0.5f);

        const vec2d delta_line = (e2.texel - e1.texel) / (e2.pos.x - e1.pos.x);

        vec2d init_line =
            e1.texel + delta_line * (float(x_start) + 0.5 - e1.pos.x);
        for (int x = x_start; x < x_end; x++, init_line += delta_line) {
            // put pixel (x, y)
            // get pixel
            auto b = std::fmod(init_line.y * tex_height, tex_clamp_y);
            auto pixel = get_pixel(
                texture,
                int(std::fmod(init_line.x * tex_width, tex_clamp_x)),
                int(std::fmod(init_line.y * tex_height, tex_clamp_y)));
            auto z = util::vec::interpolate_z(global_t->pts, vec2d(x, y));
            zbuf->put_pixel(vec3d(x, y, z), pixel);
        }
    }
}
inline void draw_flat_top_triangle_texture(const TexVertex& v0,
                                           const TexVertex& v1,
                                           const TexVertex& v2,
                                           const SDL_Surface* const texture,
                                           ZBuffer* zbuf)
{
    const float delta_y = v2.pos.y - v0.pos.y;
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
    const float delta_y = v2.pos.y - v0.pos.y;
    const auto d1 = (v1 - v0) / delta_y;
    const auto d2 = (v2 - v0) / delta_y;
    TexVertex edge(v0);

    draw_flat_triangle_texture(v0, v1, v2, d1, d2, edge, texture, zbuf);
}
inline void draw_triangle_texture(triangle pos_tri,
                                  triangle tex_tri,
                                  const SDL_Surface* const texture,
                                  ZBuffer* zbuf)
{
    global_t = &pos_tri;

    TexVertex v0{ pos_tri.pts[0], tex_tri.pts[0] };
    TexVertex v1{ pos_tri.pts[1], tex_tri.pts[1] };
    TexVertex v2{ pos_tri.pts[2], tex_tri.pts[2] };

    if (v1.pos.y < v0.pos.y)
        std::swap(v0, v1);
    if (v2.pos.y < v1.pos.y)
        std::swap(v1, v2);
    if (v1.pos.y < v0.pos.y)
        std::swap(v0, v1);

    if (v0.pos.y == v1.pos.y) // natural flat-top triangle
    {
        if (v1.pos.x < v0.pos.x)
            std::swap(v0, v1);
        draw_flat_top_triangle_texture(v0, v1, v2, texture, zbuf);
    } else if (v1.pos.y == v2.pos.y) // natural flat-bottom triangle
    {
        if (v2.pos.x < v1.pos.x)
            std::swap(v1, v2);
        draw_flat_bottom_triangle_texture(v0, v1, v2, texture, zbuf);
    } else // genera
    {
        // split
        const float split = (v1.pos.y - v0.pos.y) / (v2.pos.y - v0.pos.y);

        const TexVertex v3(util::vec::interpolate(v0.pos, v2.pos, split),
                           util::vec::interpolate(v0.texel, v2.texel, split));
        if (v1.pos.x < v3.pos.x) {
            draw_flat_bottom_triangle_texture(v0, v1, v3, texture, zbuf);
            draw_flat_top_triangle_texture(v1, v3, v2, texture, zbuf);
        } else {
            draw_flat_bottom_triangle_texture(v0, v3, v1, texture, zbuf);
            draw_flat_top_triangle_texture(v3, v1, v2, texture, zbuf);
        }
    }
    global_t = nullptr;
}

}; // namespace draw
}; // namespace util