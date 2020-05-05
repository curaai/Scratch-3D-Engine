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

    void render(std::vector<triangle> tris);
    void update(void); 
    bool running(void) { return isRunning; }

public: 
    SDL_Window* _window; 
    SDL_Renderer* _renderer; 
    bool isRunning;

    std::string name;
    int w;
    int h; 
private:
    const int min_x=0;
    const int min_y=0;
    const float min_z=0.0f;
    const float max_z=1.0f;

    mat44 screen_mat;
};
