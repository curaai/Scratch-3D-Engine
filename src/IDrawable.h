#pragma once 

#include "bean.h"
#include <SDL.h>

class IDrawable
{
public:
    IDrawable(rgba c) : c(c) {};
    ~IDrawable(){};
    virtual void draw(SDL_Renderer* rend)=0;
    rgba c;    
};
