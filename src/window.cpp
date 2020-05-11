#include "window.h"
#include "util_draw.h"

#include <iostream>


Window::Window(const string name, const int width, const int height)
    : name(name)
    , w(width)
    , h(height)
    , is_running(true)
    , zbuffer(w, h)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow(
        name.c_str(), 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        w, 
        h,
        0
    );
    _renderer = SDL_CreateRenderer(_window, -1, 0);

    // initialize view port matrix 
    mat44 reflection_mat = util::mat::getScaleMat(vec3d {1, -1, 1});
    mat44 scale_mat = util::mat::getScaleMat(vec3d{w/2.f, h/2.f, max_z - min_z});
    mat44 translate_mat = util::mat::getTranslationMat(vec3d{min_x + w/2.f, min_y + h/2.f, min_z});
    _screen_mat = translate_mat * scale_mat * reflection_mat;
}

Window::~Window()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

void Window::render(const Drawable& obj, std::vector<std::pair<triangle, bool>> fragments)
{
    for(int i=0; i<fragments.size(); i++) {
        auto fragment = fragments[i];
        if(!fragment.second)
            continue;

        auto& tri = fragment.first;
        tri.pts[0] = _screen_mat * tri.pts[0];
        tri.pts[1] = _screen_mat * tri.pts[1];
        tri.pts[2] = _screen_mat * tri.pts[2];
        
        // draw_triangle(_renderer, tri);
        zbuffer.fill_triangle(tri, util::draw::triangle_indices(tri), obj.mesh_.colors[i]);
    }
}

void Window::update()
{
    SDL_RenderClear(_renderer);

    for(int i=0; i<h; i++) {
        for(int j=0; j<w; j++) {
            const auto& c = zbuffer.color_value(j, i);
            SDL_SetRenderDrawColor(_renderer, c.r, c.g, c.b, c.a);
            SDL_RenderDrawPoint(_renderer, j, i);
            SDL_SetRenderDrawColor(_renderer,0,0,0,255);
        }
    }

    SDL_RenderPresent(_renderer);
    zbuffer.clear();
}



SDL_Color Window::pixel(uint x, uint y)
{
    return zbuffer.color_value(x, y);
}