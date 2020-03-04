#include "user.h"
#include "utils.h"

#include <math.h>


User::User(float x, float y, rgba c)
    : IDrawable()
    , color(c)
{
    pos = Point {x,y};
}

void User::draw(SDL_Renderer* rend)
{
    util::sdl::draw_circle(rend, pos.x, pos.y, size, color, true);

    // set line length as 5 temporary 

    SDL_SetRenderDrawColor(rend, color.r, color.g, color.b, color.a);

    double _ori = deg2rad(ori);

    int lineX = cos(_ori) * 50;
    int lineY = sin(_ori) * 50;
    SDL_RenderDrawLineF(rend, pos.x, pos.y, pos.x+lineX, pos.y-lineY);

    SDL_SetRenderDrawColor(rend, 0,0,0,255);
}

void User::turn(SDL_Keycode dir)
{
    if(dir == SDLK_LEFT)
        ori += oriSensitivity;
    else if(dir == SDLK_RIGHT)
        ori -= oriSensitivity;
}