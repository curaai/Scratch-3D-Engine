#include "RelativeWindow.h"
#include <vector>

void RelativeWindow::render(vector<Object*>& renderObjects)
{
    SDL_RenderClear(_renderer);

    user->draw(_renderer, true);
    for(Object* object : renderObjects)
        object->draw(_renderer, user);

    SDL_RenderPresent(_renderer);
}
