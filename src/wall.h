#pragma once 

#include "object.h"

class Wall : public Object
{
public: 
    Wall(Point a, Point b, rgba c);
    ~Wall(){};
    void draw(SDL_Renderer* rend) override;
    void draw(SDL_Renderer* rend, User* user) override;
    Point getRelativeCoord(const Point& pt, User* user);
    
    Point a;
    Point b;
};