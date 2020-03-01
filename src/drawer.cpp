#include <SDL.h> 

#include <string>
#include <cstdint>

#define MAP_W 512
#define MAP_H 512

class Drawer
{
public: 
    Drawer(SDL_Window* parent_window, const unsigned int w, const unsigned int h);

public: 
    SDL_Surface *img; 
    SDL_Renderer *rend;
    uint32_t** arr;
private:
    SDL_Window* _window;
    int h, w; 

};

Drawer::Drawer(SDL_Window* parent_window, const unsigned int w, const unsigned int h)
{   
    arr = new uint32_t[h][w]();
    this->w = w;
    this->h = h;
}
