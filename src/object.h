#pragma once 

#include "IDrawable.h"
#include "user.h"

class Object : public IDrawable
{
public:
    Object(rgba c) : IDrawable(c) {};
    ~Object(){};

    virtual void draw(SDL_Renderer* rend, User* user)=0;
};