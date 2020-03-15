#pragma once 

#include "../user.h"
#include "../world.h"

#include <math.h>

class RayEngine
{
public:
    RayEngine(User& user, World& world);
    ~RayEngine(){};
    void draw2d(SDL_Renderer* rend);
    void draw3d(SDL_Renderer* rend);

private:
    User& user;
    World& world;

    // field of view, ±60° 시야각
    const float fov=55;
    // fov / world : 한 빛이 engine에 그려지는 width 
    const float rayWidth; 
    const float maxRayDistance;
};
