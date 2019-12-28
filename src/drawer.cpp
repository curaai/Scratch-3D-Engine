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

// MVC 
// View 
class Window
{
public:
    Window(const std::string name, const uint8_t width, const uint8_t height);

public: 
    Drawer drawer;

private: 
    SDL_Window* _window; 
    std::string name;
    uint8_t w;
    uint8_t h; 
}

Window::Window(const std::string name, const uint8_t width, const uint8_t height)
{
    this->name = name;
    w = width;
    h = height;

    _window = SDL_CreateWindow(
        name.c_str(), 
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        w, 
        h,
        SDL_WINDOW_SHOWN
    );

    drawer = new Drawer {this, w, h};
}