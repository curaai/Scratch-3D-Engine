#pragma once 

#include "IDrawable.h"

#include <SDL.h>
#include <string>
#include <cstdint>

using namespace std;

class Window
{
public:
    Window(const string name, const int width, const int height);
    ~Window();

    void render(Drawable& drawObj);
    void update(void); 
    bool running(void) { return isRunning; }

public: 
    SDL_Window* _window; 
    SDL_Renderer* _renderer; 
    bool isRunning;

    std::string name;
    int w;
    int h; 
};
