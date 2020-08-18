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

    void putPixel(vec3d pos, const SDL_Color& pixel)
    {
        const int x = static_cast<int>(pos[0]);
        const int y = static_cast<int>(pos[1]);
        if (pos[0] < 0 || w <= pos[0] || pos[1] < 0 || h <= pos[1])
            return;
        if (zbuf[y][x] > pos[2]) {
            zbuf[y][x] = pos[2];
            cbuf[y][x] = pixel;
        }
    }
    float depthValue(uint x, uint y) const { return zbuf[y][x]; }
    const SDL_Color& colorValue(uint x, uint y) const { return cbuf[y][x]; }

private:
    const int w;
    const int h;
    float** zbuf;
    SDL_Color** cbuf;
};