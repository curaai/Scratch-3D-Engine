#include "world.h"

World::World(int width, int height)
    : width(width)
    , height(height)
{ 
}

void World::addElement(Wall* element)
{
    elements.push_back(element);
}

std::vector<Wall*>& World::getElements(void)
{
    return elements;
}