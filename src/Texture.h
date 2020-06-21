#pragma once

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#error Windows_OS
#elif defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include "SDL.h"
#include "SDL_image.h"
#endif

#include <string>

struct Texture
{
    Texture(const std::string& color_path)
        : color_path(color_path)
        , isColored(false)
    {
        color_map = IMG_Load(color_path.c_str());
        auto res = SDL_GetError();
    }
    Texture(SDL_Color c)
        : isColored(true)
    {
        solid_color.r = c.r;
        solid_color.g = c.g;
        solid_color.b = c.b;
        solid_color.a = c.a;
    }

    SDL_Color pixel(float x, float y) const
    {
        if (isColored) {
            return solid_color;
        } else {
            const uint _x = std::fmod(color_map->w * x, color_map->w - 1.0f);
            const uint _y = std::fmod(color_map->h * y, color_map->h - 1.0f);
            return pixel(_x, _y);
        }
    }
    SDL_Color pixel(const uint x, const uint y) const
    {
        if (!isColored)
            return solid_color;

        int bpp = color_map->format->BytesPerPixel;
        /* Here p is the address to the pixel we want to retrieve */
        uint8_t* p =
            (uint8_t*)color_map->pixels + y * color_map->pitch + x * bpp;
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
        SDL_GetRGB(_pixel, color_map->format, &rgb.r, &rgb.g, &rgb.b);
        rgb.a = 255;
        return rgb;
    }

    bool isColored;
    SDL_Color solid_color;

    // texture elements
    std::string color_path;
    SDL_Surface* color_map;
    // height elements
    std::string height_path;
    SDL_Surface* height_map;
    // normal elements
    std::string normal_path;
    SDL_Surface* normal_map;
    // // ambient elements
    // std::string ambient_path;
    // SDL_Surface* ambient_map;
};