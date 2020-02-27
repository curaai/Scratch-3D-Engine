#pragma once 

#include "point.h"
#include <vector>


class Pt3d
{
public:
    Pt3d(int x, int y, int z=0): x(x), y(y), z(z){};
    int x, y, z;
};


class Block 
{
public:
    Block(std::vector<Pt3d> pts) : pts(pts) {};
public:
    bool isFilled;
protected:
    std::vector<Pt3d> pts;      
};
