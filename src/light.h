#pragma once

#include "Drawable.h"

// Like SUN
class Light : public Drawable
{
public:
    Light(void)
        : Drawable(Mesh::loadFromObj("sphere.obj"),
                   Texture(SDL_Color{ 255, 255, 255, 255 }))
    {}
    vec3d lightColor(void)
    {
        auto c = texture.solid_color;
        vec3d v{ (float)c.r / 255, (float)c.g / 255, (float)c.b / 255 };
        return v;
    }
};