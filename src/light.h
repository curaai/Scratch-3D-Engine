#pragma once

#include "Drawable.h"

// Like SUN
class Light : public Drawable
{
public:
    Light(void)
        : Drawable(Mesh::loadFromObj("sphere.obj"),
                   Resource(SDL_Color{ 255, 255, 255, 255 }))
    {}
    vec3d lightColor(void)
    {
        auto c = resource.color;
        vec3d v{ c.r / 255, c.g / 255, c.b / 255 };
        return v;
    }
};