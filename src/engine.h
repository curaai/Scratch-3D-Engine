#include "IDrawable.h"
#include "camera.h"

class Engine
{
public:
    Engine();
    ~Engine();

    std::vector<std::pair<triangle, bool>> draw(Drawable* m, Camera* cam);
    std::vector<std::pair<triangle, bool>> culling(
        const std::vector<triangle>& triangles);

    void set_projection(float aspect_ratio, float fov, float near, float far);

private:
    mat44 proj_mat;
};
