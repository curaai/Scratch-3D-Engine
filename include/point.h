#pragma once 

class Pt3d
{
public:
    Pt3d(int x, int y, int z=0): x(x), y(y), z(z){};
    int x, y, z;
};