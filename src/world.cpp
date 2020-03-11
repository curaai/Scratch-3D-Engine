#include "world.h"

void World::addElement(Wall* element)
{
    elements.push_back(element);
}

std::vector<Wall*>& World::getElements(void)
{
    return elements;
}