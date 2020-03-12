#pragma once 

#include "../user.h"
#include "../world.h"

#include <math.h>

class RayEngine
{
public:
    RayEngine(User& user, World& world);
    ~RayEngine(){};
    void draw(SDL_Renderer* rend);

private:
    User& user;
    World& world;

    // field of view, ±60° 시야각
    const float fov=60;
    // fov / world : 한 빛이 engine에 그려지는 width 
    const float rayWidth; 
    const float maxRayDistance;
};
