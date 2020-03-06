#pragma once 

#include "IDrawable.h"

class Wall : public IDrawable
{
public: 
    Wall(Point a, Point b, rgba c);
    ~Wall(){};
    void draw(SDL_Renderer* rend) override;
    
    Point a;
    Point b;
};