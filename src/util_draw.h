#pragma once

#include "Mesh.h"
#include "zbuffer.h"

namespace util {
namespace draw {

inline SDL_Color GetPixel(const SDL_Surface* surface,
                          const uint x,
                          const uint y)
{
    if (0 > x || 0 > y || surface->w <= x || surface->h <= y)
        throw std::out_of_range("Invalid texcoordinate");

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
    SDL_GetRGBA(_pixel, surface->format, &rgb.r, &rgb.g, &rgb.b, &rgb.a);
    return rgb;
}
inline SDL_Color GetPixel(const SDL_Surface* surface, const vec2d& tex_coord)
{
    if (0 > tex_coord[0] || 1 < tex_coord[0] || 0 > tex_coord[1] ||
        1 < tex_coord[1])
        throw std::out_of_range("Invalid texcoordinate");

    const uint _x = std::fmod(surface->w * tex_coord[0], surface->w - 1.0f);
    const uint _y = std::fmod(surface->h * tex_coord[1], surface->h - 1.0f);
    return GetPixel(surface, _x, _y);
}

}; // namespace draw
}; // namespace util