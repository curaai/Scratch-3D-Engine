#pragma once 

#include "mesh.h"


class Camera 
{
public:
    Camera();
    explicit Camera(vec3d pos);
    ~Camera();

    const mat44 view_matrix(void);

    void setPos(vec3d v) { pos = v; }
    void setRotation(vec3d v) { rotation = v; }

private:
    vec3d pos;
    vec3d at;
    vec3d up {0, 1, 0};
    vec3d rotation {0, 0, 0};
};