#pragma once 

#include "IDrawable.h"
#include "bean.h"

class User : public IDrawable
{
public:
    User(float x, float y, rgba c);

public:
    void draw(SDL_Renderer* rend) override;

public:
    rgba color;
    Point pos;    
    int size=5;
};