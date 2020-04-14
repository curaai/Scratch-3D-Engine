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

void Window::render(Drawable& drawObj)
{
    SDL_RenderClear(_renderer);

    drawObj.draw(_renderer);

    SDL_RenderPresent(_renderer);
}

void Window::update()
{

}