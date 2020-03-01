#include "window.h"

#include "utils.h"
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

void Window::handleEvent()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) 
    {
    case SDL_QUIT:
        break;
    }
}

void Window::render()
{
    SDL_RenderClear(_renderer);

    auto c = rgba {255, 0, 0, 255};
    util::sdl::draw_circle(_renderer, 300, 300, 10, c, true);

    SDL_RenderPresent(_renderer);
}

void Window::update()
{

}