#include "wall.h"
#include "utils.h"

Wall::Wall(Point a, Point b, rgba c)
    : Object(c)
    , a(a)
    , b(b)
{}

void Wall::draw(SDL_Renderer* rend)
{
    SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
    SDL_RenderDrawLineF(rend, a.x, a.y, b.x, b.y);
    SDL_SetRenderDrawColor(rend, 0,0,0,255);
}

void Wall::draw(SDL_Renderer* rend, User* user)
{
    SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
    Point _a, _b;

    _a = getRelativeCoord(a, user);
    _b = getRelativeCoord(b, user);

    SDL_RenderDrawLineF(rend, _a.x, _a.y, _b.x, _b.y);

    SDL_SetRenderDrawColor(rend,0,0,0,255);
}
Point Wall::getRelativeCoord(const Point& pt, User* user)
{
    float ori = deg2rad(450 - user->ori);
    Point _pt = pt - user->pos;
    float newx = cos(ori) * _pt.x + sin(ori) * _pt.y;
    float newy = - sin(ori) * _pt.x + cos(ori) * _pt.y;
    return (Point{newx, newy} + user->pos);
}