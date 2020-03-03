#pragma once 

#include <SDL.h>

class IDrawable
{
public:
    IDrawable(){};
    ~IDrawable(){};
    virtual void draw(SDL_Renderer* rend) {};
};
