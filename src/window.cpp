#include "window.h"

#include <iostream>


Window::Window(const string name, const int width, const int height)
    : name(name)
    , w(width)
    , h(height)
    , isRunning(true)
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
    screen_mat = translate_mat * scale_mat * reflection_mat;
}
Window::~Window()
{
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
}

void Window::render(std::vector<triangle> tris)
{
    SDL_RenderClear(_renderer);

    for(auto tri : tris) {
        tri.pts[0] = screen_mat * tri.pts[0];
        tri.pts[1] = screen_mat * tri.pts[1];
        tri.pts[2] = screen_mat * tri.pts[2];
        draw_triangle(_renderer, tri);
    }

    SDL_RenderPresent(_renderer);
}

void Window::update()
{

}