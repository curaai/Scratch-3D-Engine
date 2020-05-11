#pragma once 

#include "mesh.h"


struct pos {
    pos(float x, float y) : x(static_cast<int>(x)), y(static_cast<int>(y)){}
    pos(int x, int y) : x(x), y(y) {}
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

    namespace {
        inline void fill_bottom_flat_triangle(pos v1, pos v2, pos v3, std::vector<line> &lines)
        {
            float invslope1 = (float)(v2.x - v1.x) / (v2.y - v1.y);
            float invslope2 = (float)(v3.x - v1.x) / (v3.y - v1.y);

            float curx1 = v1.x;
            float curx2 = v1.x;

            for (int scanlineY = v1.y; scanlineY <= v2.y; scanlineY++)
            {
                auto _min = std::min(static_cast<int>(curx1), static_cast<int>(curx2));
                auto _max = std::max(static_cast<int>(curx1), static_cast<int>(curx2));
                lines.push_back(line{pos{_min, scanlineY}, pos{_max, scanlineY}});
                curx1 += invslope1;
                curx2 += invslope2;
            }
        }

        inline void fill_top_flat_triangle(pos v1, pos v2, pos v3, std::vector<line> &lines)
        {
            float invslope1 = (float)(v3.x - v1.x) / (v3.y - v1.y);
            float invslope2 = (float)(v3.x - v2.x) / (v3.y - v2.y);

            float curx1 = v3.x;
            float curx2 = v3.x;

            for (int scanlineY = v3.y; scanlineY > v1.y; scanlineY--)
            {
                auto _min = std::min(static_cast<int>(curx1), static_cast<int>(curx2));
                auto _max = std::max(static_cast<int>(curx1), static_cast<int>(curx2));
                lines.push_back(line{pos{_min, scanlineY}, pos{_max, scanlineY}});
                curx1 -= invslope1;
                curx2 -= invslope2;
            }
        }
    } // namespace

    inline std::vector<line> triangle_indices(const triangle& t)
    {
        std::vector<line> lines;
        pos v1 {t.pts[0].x, t.pts[0].y};
        pos v2 {t.pts[1].x, t.pts[1].y};
        pos v3 {t.pts[2].x, t.pts[2].y};

        /* at first sort the three vertices by y-coordinate ascending so v1 is the topmost vertice */
        if (v2.y < v1.y)
            std::swap(v2, v1);
        if (v3.y < v1.y)
            std::swap(v3, v1);
        if (v3.y < v2.y)
            std::swap(v3, v2);

        /* here we know that v1.y <= v2.y <= v3.y */
        /* check for trivial case of bottom-flat triangle */
        if (v2.y == v3.y)
        {
            fill_bottom_flat_triangle(v1, v2, v3, lines);
        }
        /* check for trivial case of top-flat triangle */
        else if (v1.y == v2.y)
        {
            fill_top_flat_triangle(v1, v2, v3, lines);
        }
        else
        {
            /* general case - split the triangle in a topflat and bottom-flat one */
            pos v4 {static_cast<int>(v1.x + ((v2.y - v1.y) / (float)(v3.y - v1.y)) * (v3.x - v1.x)), static_cast<int>(v2.y)};
            fill_bottom_flat_triangle(v1, v2, v4, lines);
            fill_top_flat_triangle(v2, v4, v3, lines);
        }
        return lines;
    }
};    // namespace draw
};    // namespace util