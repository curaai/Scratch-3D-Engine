#pragma once
#include <algorithm>
#include <cmath>

class ZBuffer
{
public:
    ZBuffer(const int w, const int h)
        : w(w)
        , h(h)
    {
        zbuf = new float*[h];
        cbuf = new SDL_Color*[h];
        for (int i = 0; i < h; i++) {
            zbuf[i] = new float[w];
            std::fill_n(zbuf[i], w, 1.0f);
            cbuf[i] = new SDL_Color[w];
        }
    }
    ~ZBuffer(void)
    {
        for (int i = 0; i < h; i++) {
            delete[] cbuf[i];
            delete[] zbuf[i];
        }
        delete[] zbuf;
        delete[] cbuf;
    }
    void clear(void)
    {
        for (int i = 0; i < h; i++) {
            std::fill_n(zbuf[i], w, 1.0f);
            std::fill_n(cbuf[i], w, SDL_Color{ 0, 0, 0, 0 });
        }
    }

    void put_pixel(vec3d pos, const SDL_Color& pixel)
    {
        const int x = static_cast<int>(pos.x);
        const int y = static_cast<int>(pos.y);
        if (pos.x < 0 || w <= pos.x || pos.y < 0 || h <= pos.y)
            return;
        if (zbuf[y][x] > pos.z) {
            zbuf[y][x] = pos.z;
            cbuf[y][x] = pixel;
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