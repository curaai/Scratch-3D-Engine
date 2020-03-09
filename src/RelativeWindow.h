#pragma once 

#include "window.h"
#include "object.h"

class RelativeWindow : public Window
{
public:
    RelativeWindow(const string name, const int width, const int height, User* user)
        : Window(name, width, height)
        , user(user) {};
    ~RelativeWindow(){};
    void render(vector<Object*>& renderObjects);

protected:
    User* user;
};