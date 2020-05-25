#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>

struct Resource
{
    Resource(const std::string rsc_path)
        : rsc_path(rsc_path)
    {
        rsc = IMG_Load(rsc_path.c_str());
        auto res = SDL_GetError();
    }

    SDL_Color pixel(const uint x, const uint y)
    {
        int bpp = rsc->format->BytesPerPixel;
        /* Here p is the address to the pixel we want to retrieve */
        uint8_t* p = (uint8_t*)rsc->pixels + y * rsc->pitch + x * bpp;
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
        SDL_GetRGB(_pixel, rsc->format, &rgb.r, &rgb.g, &rgb.b);
        return rgb;
    }

    const std::string rsc_path;
    SDL_Surface* rsc;
};