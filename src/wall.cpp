#include "wall.h"

Wall::Wall(Point a, Point b, rgba c)
    : IDrawable(c)
    , a(a)
    , b(b)
{}

void Wall::draw(SDL_Renderer* rend)
{
    SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLineF(rend, a.x, a.y, b.x, b.y);
    SDL_SetRenderDrawColor(rend, 0,0,0,255);
}