#include "window.h"

Window::Window(const string name, const uint8_t width, const uint8_t height)
    : name(name)
    , w(width)
    , h(height)
    , isRunning(true)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow(
        name.c_str(), 
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        w, 
        h,
        SDL_WINDOW_SHOWN
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
    SDL_RenderPresent(_renderer);
}
