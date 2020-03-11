#include "RayCasting.h"
#include "../utils.h"


RayEngine::RayEngine(User& user, World& world)
    : user(user)
    , world(world)
{

}


void RayEngine::draw(SDL_Renderer* rend)
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
