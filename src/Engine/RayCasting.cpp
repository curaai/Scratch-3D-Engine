#include "RayCasting.h"
#include "../utils.h"

#include <cmath>


RayEngine::RayEngine(User& user, World& world)
    : user(user)
    , world(world)
    , rayWidth(world.width / (fov + fov))
    , maxRayDistance(world.width + world.height)
{
}


void RayEngine::draw3d(SDL_Renderer* rend)
{
    const Point& pos = user.pos;
    // shoot ray from left fov to right 
    for (float theta=user.ori-fov; theta < user.ori+fov; theta+=0.5)
    {
        // stretch ray until get out map 
        double _ori = deg2rad(theta);
        float c=0, s=0;
        float _c = cos(_ori);
        float _s = sin(_ori);
        while((pos.x + c < world.width && pos.y+s < world.height) &&
              (0 < pos.x+c && 0 < pos.y+s)) {
            c += _c;
            s -= _s;
        }
        Point rayEnd {c+pos.x, s+pos.y};
        if(rayEnd.x < 0)
            rayEnd.x = 0;
        if(rayEnd.y < 0)
            rayEnd.y = 0;

        // check ray stuck on wall
        Point cross;
        bool isCross = false;
        for(Wall* w : world.getElements()) {
            if (getIntersectPoint(w->a, w->b, pos, rayEnd, &cross)) {
                rayEnd = cross;

                rgba c = w->c;
                const float angle = theta - (user.ori-fov);
                // draw ray
                // MaxRayLengthOfWorld - curRayLength => dist
                auto dist = (maxRayDistance - pos.eucDist(rayEnd)) / maxRayDistance * world.height;
                
                SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
                auto drawRect = SDL_FRect();
                // y + dist + y == world.height
                drawRect.x = angle * rayWidth;
                drawRect.y = (world.height - dist) / 2;
                drawRect.w = rayWidth;
                drawRect.h = dist;
                SDL_RenderDrawRectF(rend, &drawRect);
                SDL_SetRenderDrawColor(rend, 0,0,0,255);
            }
        }
    }
}

void RayEngine::draw2d(SDL_Renderer* rend)
{
    const Point& pos = user.pos;
    // shoot ray from left fov to right 
    for (float theta=user.ori-fov; theta < user.ori+fov; theta+=0.5)
    {
        // stretch ray until get out map 
        double _ori = deg2rad(theta);
        float c=0, s=0;
        float _c = cos(_ori);
        float _s = sin(_ori);
        while((pos.x + c < world.width && pos.y+s < world.height) &&
              (0 < pos.x+c && 0 < pos.y+s)) {
            c += _c;
            s -= _s;
        }
        Point rayEnd {c+pos.x, s+pos.y};
        if(rayEnd.x < 0)
            rayEnd.x = 0;
        if(rayEnd.y < 0)
            rayEnd.y = 0;

        // check ray stuck on wall
        Point cross;
        for(Wall* w : world.getElements()) {
            bool isCross = getIntersectPoint(w->a, w->b, pos, rayEnd, &cross);
            if (isCross)
                rayEnd = cross;
        }

        // draw ray 
        int res = SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
        res = SDL_RenderDrawLineF(rend, pos.x, pos.y, rayEnd.x, rayEnd.y);
        res = SDL_SetRenderDrawColor(rend, 0,0,0,255);
    }
}