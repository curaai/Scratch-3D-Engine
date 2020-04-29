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
        tri.pts[0].x = tri.pts[0].x * w/2 + w/2;
        tri.pts[0].y = tri.pts[0].y * h/2 + h/2;
        tri.pts[1].x = tri.pts[1].x * w/2 + w/2;
        tri.pts[1].y = tri.pts[1].y * h/2 + h/2;
        tri.pts[2].x = tri.pts[2].x * w/2 + w/2;
        tri.pts[2].y = tri.pts[2].y * h/2 + h/2;
        draw_triangle(_renderer, tri);
    }

    SDL_RenderPresent(_renderer);
}

void Window::update()
{

}