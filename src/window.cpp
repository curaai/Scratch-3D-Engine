#include "window.h"
#include "util_draw.h"

#include <iostream>

Window::Window(const string name, const int width, const int height)
    : name(name)
    , w(width)
    , h(height)
    , is_running(true)
    , _zbuffer(w, h)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow(
        name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    _renderer = SDL_CreateRenderer(_window, -1, 0);

    // initialize view port matrix
    Mat44 reflection_mat = util::mat::GetScaleMat(vec3d{ 1, -1, 1 });
    Mat44 scale_mat =
        util::mat::GetScaleMat(vec3d{ w / 2.f, h / 2.f, max_z - min_z });
    Mat44 translate_mat = util::mat::GetTranslationMat(
        vec3d{ min_x + w / 2.f, min_y + h / 2.f, min_z });
    _screen_mat = translate_mat * scale_mat * reflection_mat;
}

Window::~Window()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

void Window::render(const Drawable& obj, const std::vector<Fragment>& fragments)
{
    for (const auto& fragment : fragments) {
        if (fragment.is_culled)
            continue;

        for (const auto& fraxel : fragment.fraxels) {
            auto color = obj.resource.pixel(fraxel.texel[0], fraxel.texel[1]);
            _zbuffer.putPixel(fraxel.pixel, color);
        }
    }
}

void Window::update()
{
    SDL_RenderClear(_renderer);

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            const auto& c = _zbuffer.colorValue(j, i);
            SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
            SDL_RenderDrawPoint(_renderer, j, i);
            SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
        }
    }

    SDL_RenderPresent(_renderer);
    _zbuffer.clear();
}

SDL_Color Window::pixel(uint x, uint y)
{
    return _zbuffer.colorValue(x, y);
}