#include "mesh.h"

class Camera 
{
public:
    Camera();
    explicit Camera(vec3d pos);
    ~Camera();

    void setPos(vec3d v) { pos = v; }
    void setRotation(vec3d v) { rotation = v; }
    vec3d getPos(void) { return pos; }
    vec3d getRotation(void) { return rotation; }

    void calcBasis(void);

private:
    vec3d pos;
    vec3d at;
    vec3d up {0, 1, 0};
    vec3d rotation {0, 0, 0};

public:
    mat44 viewMat;
};