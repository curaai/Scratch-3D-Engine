#pragma once 

#include "user.h"
#include "wall.h"

#include <vector>

class World
{
public:
    World(){};
    ~World(){};

public:
    void addElement(Wall* element);
    virtual std::vector<Wall*>& getElements(void);

public:
    const int width = 320;
    const int height = 320;
private:
    std::vector<Wall*> elements;
};