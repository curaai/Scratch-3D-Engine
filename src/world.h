#pragma once 

#include "IDrawable.h"

#include <vector>

class World
{
public:
    World(){};
    ~World(){};

public:
    void addElement(IDrawable* element);
    std::vector<IDrawable*>& getElements(void);

private:
    std::vector<IDrawable*> elements;
};