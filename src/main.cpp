#include "Rasterizer.h"
#include "VertexShader.h"
#include "camera.h"
#include "window.h"

#include <ctime>
#include <iostream>

constexpr uint w = 480;
constexpr uint h = 480;

using namespace std;

void f()
{
    clock_t begin = clock();

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[])
{
    Drawable drawObj{ Mesh::loadFromObj("resource/cube.obj", true),
                      Resource{ "resource/gradation.png" } };
    drawObj.setTranslate(vec3d{ 0, 0, 8.0f });
    Camera cam{ vec3d{ 0, 0, 0 }, w / h, 60 };
    Window* win = new Window{ "3D engine", w, h };

    float t = 0;

    SDL_Keycode key;
    SDL_Event event;
    while (win->running()) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    win->is_running = false;
                    break;
            }
        }

        drawObj.setRotate(vec3d{ t, 0, -t });
        auto vst_list = VertexShader::vertexing(&drawObj, &cam);
        auto fragments = Rasterizer::rasterize(win, vst_list);

        t += 1;

        win->render(drawObj, fragments);
        win->update();
        SDL_RenderPresent(win->_renderer);
    }
    delete win;

    return 0;
}
