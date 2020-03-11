#pragma once 

#include "window.h"
#include "wall.h"

class RelativeWindow : public Window
{
public:
    RelativeWindow(const string name, const int width, const int height, User* user);
    ~RelativeWindow(){};
    void render(vector<Wall*>& renderObjects);

public:
    bool relativeMode=false;
protected:
    User* user;
};