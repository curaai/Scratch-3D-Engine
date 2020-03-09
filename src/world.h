#pragma once 

#include "user.h"
#include "object.h"

#include <vector>

class World
{
public:
    World(){};
    ~World(){};

public:
    void addElement(Object* element);
    virtual std::vector<Object*>& getElements(void);

private:
    std::vector<Object*> elements;
};