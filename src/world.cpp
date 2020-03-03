#include "world.h"

void World::addElement(IDrawable* element)
{
    elements.push_back(element);
}

std::vector<IDrawable*>& World::getElements(void)
{
    return elements;
}