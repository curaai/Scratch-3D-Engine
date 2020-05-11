#include "util_draw.h"
#include <cmath>
#include <algorithm>

class ZBuffer
{
public:
    ZBuffer(const int w, const int h)
    : w(w), h(h)
    {
        zbuf = new float* [h];
        for(int i=0; i<h; i++) {
            zbuf[i] = new float[w];
            std::fill_n(zbuf[i], w, 1.0f); 
        }

        cbuf = new SDL_Color* [h];
        for(int i=0; i<h; i++)
            cbuf[i] = new SDL_Color[w];
    }
    ~ZBuffer(void)
    {
        for(int i=0; i<h; i++)
            delete[] zbuf[i];
        delete[] zbuf;
        for(int i=0; i<h; i++)
            delete[] cbuf[i];
        delete[] cbuf;
    }
    void clear(void)
    {
        for(int i=0; i<h; i++) {
            std::fill_n(zbuf[i], w, 1.0f); 
        }
        for(int i=0; i<h; i++) {
            std::fill_n(cbuf[i], w, SDL_Color{0, 0, 0, 0}); 
        }

    }
    void fill_triangle(const triangle& t, const std::vector<line>& lines, SDL_Color c)
    {
        // interpolation
        auto length_2d = [](const vec3d& v) -> float {
            return sqrt(v.x*v.x + v.y*v.y);
        };
        auto get_weights = [&t, length_2d](const vec3d _pos, float* w) {
            w[0] = 1 / length_2d(t.pts[0] - _pos);
            w[1] = 1 / length_2d(t.pts[1] - _pos);
            w[2] = 1 / length_2d(t.pts[2] - _pos);
        };
        auto zvalue = [&t](float* w) -> float {
            return (std::abs(t.pts[0].z) * w[0] + std::abs(t.pts[1].z) * w[1] + std::abs(t.pts[2].z) * w[2])  / (w[0] + w[1] + w[2]);
        };

        for(const auto& l : lines) {
            const uint y = l.a.y;
            for(uint x=l.a.x; x <= l.b.x; x++) {
                float w[3];
                get_weights(vec3d {static_cast<float>(x), static_cast<float>(y), 0}, w);

                float z = zvalue(w);
                if(zbuf[y][x] > z) {
                    zbuf[y][x] = z;
                    cbuf[y][x] = c;
                }
            }
        }
    }

    float depth_value(uint x, uint y) const { return zbuf[y][x]; }
    const SDL_Color& color_value(uint x, uint y) const { return cbuf[y][x]; }

private:
    const int w;
    const int h;
    float** zbuf;
    SDL_Color** cbuf;
};