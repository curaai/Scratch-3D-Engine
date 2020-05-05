#include "IDrawable.h"
#include "camera.h"


class Engine
{
public:
    Engine();
    ~Engine();

    std::vector<triangle> draw(Drawable* m, Camera* cam); 
    void culling(std::vector<triangle>& triangles);

    void set_projection(float aspect_ratio, float fov, float near, float far);

private:
    mat44 proj_mat;
};