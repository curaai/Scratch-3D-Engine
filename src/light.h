#pragma once

#include "IDrawable.h"

// Like SUN
class Light : public Drawable
{
public:
    Light(void)
        : Drawable(Mesh::loadFromObj("sphere.obj"))
        , color(SDL_Color{ 255, 255, 255, 255 })
    {}
    vec3d lightColor(void)
    {
        vec3d v {
            color.r / 255,
            color.g / 255,
            color.b / 255,
        };
        return v;
    }

private:
    SDL_Color color;
};