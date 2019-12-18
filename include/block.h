#pragma once 

#include "point.h"
#include <vector>

class Block 
{
public:
    bool isFilled;
protected:
    std::vector<Pt3d> pts;
};
