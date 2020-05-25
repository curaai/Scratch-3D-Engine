#pragma once

#include "vec.h"

class TexVertex
{
public:
    vec3d pos;
    vec2d texel;

    TexVertex(const vec3d& pos, const vec2d texel)
        : pos(pos)
        , texel(texel)
    {}

    TexVertex operator+(const TexVertex& tv) const
    {
        return TexVertex(*this) += tv;
    }
    TexVertex& operator+=(const TexVertex& tv)
    {
        pos += tv.pos;
        texel += tv.texel;
        return *this;
    }
    TexVertex operator-(const TexVertex& tv) const
    {
        return TexVertex(*this) -= tv;
    }
    TexVertex& operator-=(const TexVertex& tv)
    {
        pos -= tv.pos;
        texel -= tv.texel;
        return *this;
    }
    TexVertex operator*(float v) const { return TexVertex(*this) *= v; }
    TexVertex& operator*=(const TexVertex& tv)
    {
        pos *= tv.pos;
        texel *= tv.texel;
        return *this;
    }
    TexVertex& operator*=(const float& tv)
    {
        pos *= tv;
        texel *= tv;
        return *this;
    }
    TexVertex operator/(float v) const { return TexVertex(*this) /= v; }
    TexVertex& operator/=(const TexVertex& tv)
    {
        pos /= tv.pos;
        texel /= tv.texel;
        return *this;
    }
    TexVertex& operator/=(const float& tv)
    {
        pos /= tv;
        texel /= tv;
        return *this;
    }
};