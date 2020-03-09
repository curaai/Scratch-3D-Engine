#include "world.h"

void World::addElement(Object* element)
{
    elements.push_back(element);
}

std::vector<Object*>& World::getElements(void)
{
    return elements;
}