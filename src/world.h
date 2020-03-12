#pragma once 

#include "user.h"
#include "wall.h"

#include <vector>

class World
{
public:
    World(int width=640, int height=640);
    ~World(){};

public:
    void addElement(Wall* element);
    virtual std::vector<Wall*>& getElements(void);

public:
    const int width;
    const int height;
private:
    std::vector<Wall*> elements;
};