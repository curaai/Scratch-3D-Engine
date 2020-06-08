#pragma once

#include "Vertex.h"
#include "util_vec.h"
#include <vector>

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#error Windows_OS
#elif defined(__linux__)
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include "SDL.h"
#include "SDL_image.h"
#endif

namespace {
class TexVertex
{
public:
    vec3d wpos;
    vec3d wnormal;
    vec3d pixel;
    vec2d texel;

    TexVertex() {}
    TexVertex(const vec3d& wpos,
              const vec3d& wnormal,
              const vec3d& pixel,
              const vec2d& texel)
        : pixel(pixel)
        , texel(texel)
        , wpos(wpos)
        , wnormal(wnormal)
    {}

    TexVertex operator+(const TexVertex& tv) const
    {
        return TexVertex(*this) += tv;
    }
    TexVertex& operator+=(const TexVertex& tv)
    {
        pixel += tv.pixel;
        texel += tv.texel;
        wpos += tv.wpos;
        return *this;
    }
    TexVertex operator-(const TexVertex& tv) const
    {
        return TexVertex(*this) -= tv;
    }
    TexVertex& operator-=(const TexVertex& tv)
    {
        pixel -= tv.pixel;
        texel -= tv.texel;
        wpos -= tv.wpos;
        return *this;
    }
    TexVertex operator*(float v) const { return TexVertex(*this) *= v; }
    TexVertex& operator*=(const TexVertex& tv)
    {
        pixel *= tv.pixel;
        texel *= tv.texel;
        wpos *= tv.wpos;
        return *this;
    }
    TexVertex& operator*=(const float& tv)
    {
        pixel *= tv;
        texel *= tv;
        wpos *= tv;
        return *this;
    }
    TexVertex operator/(float v) const { return TexVertex(*this) /= v; }
    TexVertex& operator/=(const TexVertex& tv)
    {
        pixel /= tv.pixel;
        texel /= tv.texel;
        wpos /= tv.wpos;
        return *this;
    }
    TexVertex& operator/=(const float& tv)
    {
        pixel /= tv;
        texel /= tv;
        wpos /= tv;
        return *this;
    }
};
}

struct RSOutput : public VSOutput
{
    RSOutput() {}
    RSOutput(const VSOutput& vso)
        : VSOutput(vso)
    {}
    vec3d spos;
};

struct Fraxel
{
    vec3d wpos;
    vec3d pixel;
    vec2d texel;
    SDL_Color color;

    Fraxel(const vec3d& wpos, const vec3d& pixel, const vec2d& texel)
        : pixel(pixel)
        , texel(texel)
        , wpos(wpos)
    {}
    Fraxel(const vec3d& wpos,
           const vec3d& pixel,
           const vec2d& texel,
           const SDL_Color c)
        : Fraxel(wpos, pixel, texel)
    {
        color.r = c.r;
        color.g = c.g;
        color.b = c.b;
        color.a = c.a;
    }
};

class Fragment : public triangle<RSOutput>
{
public:
    std::vector<Fraxel> fraxels;
    const bool is_culled;

    Fragment(const RSOutput& a,
             const RSOutput& b,
             const RSOutput& c,
             bool is_culled)
        : is_culled(is_culled)
    {
        this->pts[0] = a;
        this->pts[1] = b;
        this->pts[2] = c;

        init_fraxels();
    }
    Fragment(triangle<vec3d> world_tri,
             triangle<vec3d> wnormal_tri,
             triangle<vec2d> tpos_tri,
             triangle<vec3d> clipped_tri,
             triangle<vec3d> screen_tri,
             bool is_culled)
        : is_culled(is_culled)
    {
        pts[0].cpos = clipped_tri[0];
        pts[1].cpos = clipped_tri[1];
        pts[2].cpos = clipped_tri[2];

        pts[0].wpos = world_tri[0];
        pts[1].wpos = world_tri[1];
        pts[2].wpos = world_tri[2];

        pts[0].wnormal = wnormal_tri[0];
        pts[1].wnormal = wnormal_tri[1];
        pts[2].wnormal = wnormal_tri[2];

        pts[0].tpos = tpos_tri[0];
        pts[1].tpos = tpos_tri[1];
        pts[2].tpos = tpos_tri[2];

        pts[0].spos = screen_tri[0];
        pts[1].spos = screen_tri[1];
        pts[2].spos = screen_tri[2];

        init_fraxels();
    }

    Tri3d sposTriangle(void) const
    {
        return Tri3d{ pts[0].spos, pts[1].spos, pts[2].spos };
    }
    Tri3d cposTriangle(void) const
    {
        return Tri3d{ pts[0].cpos, pts[1].cpos, pts[2].cpos };
    }
    Tri3d wposTriangle(void) const
    {
        return Tri3d{ pts[0].wpos, pts[1].wpos, pts[2].wpos };
    }
    Tri3d wnormalTriangle(void) const
    {
        return Tri3d{ pts[0].wnormal, pts[1].wnormal, pts[2].wnormal };
    }
    Tri2d tposTriangle(void) const
    {
        return Tri2d{ pts[0].tpos, pts[1].tpos, pts[2].tpos };
    }

private:
    void init_fraxels()
    {
        fraxels.clear();
        triangle<TexVertex> t{
            TexVertex{ pts[0].wpos, pts[0].wnormal, pts[0].spos, pts[0].tpos },
            TexVertex{ pts[1].wpos, pts[1].wnormal, pts[1].spos, pts[1].tpos },
            TexVertex{ pts[2].wpos, pts[2].wnormal, pts[2].spos, pts[2].tpos },
        };

        /* at first sort the three vertices by y-coordinate ascending so v1 is
         * the topmost vertice */
        if (t[1].pixel[1] < t[0].pixel[1])
            std::swap(t[1], t[0]);
        if (t[2].pixel[1] < t[0].pixel[1])
            std::swap(t[2], t[0]);
        if (t[2].pixel[1] < t[1].pixel[1])
            std::swap(t[2], t[1]);

        /* here we know that v1.y <= v2.y <= v3.y */
        /* check for trivial case of bottom-flat triangle */
        if (t[1].pixel[1] == t[2].pixel[1]) {
            if (t[1].pixel[0] < t[0].pixel[0])
                std::swap(t[0], t[1]);
            bottom_flat_triangle(t);
        }
        /* check for trivial case of top-flat triangle */
        else if (t[0].pixel[1] == t[1].pixel[1]) {
            if (t[1].pixel[0] < t[0].pixel[0])
                std::swap(t[0], t[1]);
            top_flat_triangle(t);
        } else {
            /* general case - split the triangle in a topflat and bottom-flat
             * one */
            const float split = (t[1].pixel[1] - t[0].pixel[1]) /
                                (t[2].pixel[1] - t[0].pixel[1]);

            const TexVertex tv(
                util::vec::Interpolate<vec3d>(t[0].wpos, t[2].wpos, split),
                util::vec::Interpolate<vec3d>(
                    t[0].wnormal, t[2].wnormal, split),
                util::vec::Interpolate<vec3d>(t[0].pixel, t[2].pixel, split),
                util::vec::Interpolate<vec2d>(t[0].texel, t[2].texel, split));
            bottom_flat_triangle(triangle<TexVertex>{ t[0], t[1], tv });
            top_flat_triangle(triangle<TexVertex>{ t[1], tv, t[2] });
        }
    }
    void bottom_flat_triangle(const triangle<TexVertex>& t)
    {
        const float delta_y = t[2].pixel[1] - t[0].pixel[1];
        const auto d1 = (t[1] - t[0]) / delta_y;
        const auto d2 = (t[2] - t[0]) / delta_y;
        TexVertex edge(t[0]);

        flat_triangle(t, d1, d2, edge);
    }
    void top_flat_triangle(const triangle<TexVertex>& t)
    {
        const float delta_y = t[2].pixel[1] - t[0].pixel[1];
        const auto d1 = (t[2] - t[0]) / delta_y;
        const auto d2 = (t[2] - t[1]) / delta_y;
        TexVertex edge(t[1]);

        flat_triangle(t, d1, d2, edge);
    }
    void flat_triangle(const triangle<TexVertex>& t,
                       const TexVertex& d1,
                       const TexVertex& d2,
                       TexVertex& e2)
    {
        TexVertex e1 = t[0];

        const int y_start = static_cast<int>(t[0].pixel[1]);
        const int y_end = static_cast<int>(t[2].pixel[1]);

        for (int y = y_start; y < y_end; y++, e1 += d1, e2 += d2) {
            const int x_start = static_cast<int>(e1.pixel[0]);
            const int x_end = static_cast<int>(e2.pixel[0]);

            TexVertex init_line = e1;
            const TexVertex delta_line =
                (e2 - e1) / (e2.pixel[0] - e1.pixel[0]);
            for (int x = x_start; x < x_end; x++, init_line += delta_line) {

                fraxels.push_back(
                    Fraxel{ init_line.wpos,
                            vec3d{ (float)x, (float)y, init_line.wpos[2] },
                            init_line.texel });
            }
        }
    };
};