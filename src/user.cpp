#include "user.h"
#include "utils.h"


User::User(float x, float y, rgba c)
    : IDrawable()
    , color(c)
{
    pos = Point {x,y};
}

void User::draw(SDL_Renderer* rend)
{
    util::sdl::draw_circle(rend, pos.x, pos.y, size, color, true);
}
