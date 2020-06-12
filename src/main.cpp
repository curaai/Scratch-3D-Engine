#include "FragmentShader.h"
#include "Rasterizer.h"
#include "User.h"
#include "VertexShader.h"
#include "window.h"

#include <ctime>
#include <iostream>

constexpr uint w = 480;
constexpr uint h = 480;

using namespace std;


int main(int argc, char* argv[])
{
    Window* win = new Window{ "3D engine", w, h };
    User user{ vec3d{ 0, 0, 0 }, w / h, 60 };

    Drawable drawObj{ Mesh::loadFromObj("resource/cube.obj", true),
                      Resource{ "resource/gradation.png" } };
    drawObj.setTranslate(vec3d{ 0, 0, 5.0f });
    Light light;
    light.setTranslate(vec3d{ 3, 3, -10 });

    FragmentShader fs{ &light, &user };

    float t = 30;

    SDL_Keycode key;
    SDL_Event event;
    while (win->running()) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    win->is_running = false;
                    break;
                case SDL_KEYDOWN: {
                    auto key = event.key.keysym.sym;
                    user.keyEvent(key);
                    break;
                }
            }
        }

        drawObj.setRotate(vec3d{ t, 0, -t });
        auto vst_list = VertexShader::vertexing(&drawObj, &user);
        auto fragments = Rasterizer::rasterize(win, vst_list);
        fragments = fs.lighting(fragments, &drawObj.resource);

        t += 1;

        win->render(fragments);
        win->update();
        SDL_RenderPresent(win->_renderer);
    }
    delete win;

    return 0;
}
