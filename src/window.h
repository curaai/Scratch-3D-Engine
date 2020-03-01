#include <SDL.h>

#include <string>
#include <cstdint>

using namespace std;

class Window
{
public:
    Window(const string name, const uint8_t width, const uint8_t height);
    ~Window();

    void handleEvent(void);
    void render(void);
    void update(void); 
    bool running(void) { return isRunning; }

private: 
    SDL_Window* _window; 
    SDL_Renderer* _renderer; 
    bool isRunning;

    std::string name;
    uint8_t w;
    uint8_t h; 
};
