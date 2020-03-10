#include "RelativeWindow.h"
#include <vector>
RelativeWindow::RelativeWindow(const string name, const int width, const int height, User* user)
    : Window(name, width, height)
    , user(user)
{
    user->isRelative = &relativeMode;
}

void RelativeWindow::render(vector<Object*>& renderObjects)
{
    SDL_RenderClear(_renderer);

    user->draw(_renderer);
    for(Object* object : renderObjects) {
        if(relativeMode)
            object->draw(_renderer, user);
        else
            object->draw(_renderer);
    }

    SDL_RenderPresent(_renderer);
}
