#include "user.h"
#include "utils.h"

#include <math.h>


User::User(float x, float y, rgba c)
    : IDrawable(c)
{
    pos = Point {x,y};
}

void User::draw(SDL_Renderer* rend)
{
    util::sdl::draw_circle(rend, pos.x, pos.y, size, c, true);

    // set line length as 5 temporary 

    SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);

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

void User::move(SDL_Keycode dir)
{
    int _ori = 0;
    switch(dir) {
    case SDLK_w:
        _ori = 0;
        break;
    case SDLK_s:
        _ori = 180;
        break;
    case SDLK_a:
        _ori = 90;
        break;
    case SDLK_d:
        _ori = 270;
        break;
    }

    double deg = deg2rad(ori + _ori);

    float newX= pos.x + cos(deg) * speed;
    float newY= pos.y - sin(deg) * speed;
    pos = Point{newX, newY}; 
}