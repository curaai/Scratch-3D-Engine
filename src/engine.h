#include "IDrawable.h"
#include "camera.h"

class Engine
{
public:
    Engine();
    ~Engine();

    IndexedTri3dList draw(Drawable* m, Camera* cam);
    IndexedTri3dList culling(const std::vector<Tri3d>& triangles);

    void set_projection(float aspect_ratio, float fov, float near, float far);

private:
    mat44 proj_mat;
};
