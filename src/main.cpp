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

    Texture texture{ "resource/brick/color.jpg" };
    texture.setTexture("resource/brick/normal.jpg",
                       "resource/brick/ambient.jpg");
    Drawable drawObj{ Mesh::loadFromObj("resource/cube.obj", true), texture };
    drawObj.setTranslate(vec3d{ 0, 0, 5.0f });

    Light light;
    light.setTranslate(vec3d{ 0, 0, -10 });

    FragmentShader fs{ &light, &user };

    float t = 0;

    unsigned int debug_flags = 0;
    debug_flags |= 1 << 5 | 1 << 11;

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
#ifndef NDEBUG
                    switch (key) {
                        case SDLK_1:
                            debug_flags ^= 1;
                            break;
                        case SDLK_2:
                            debug_flags ^= 1 << 1;
                            break;
                        case SDLK_3:
                            debug_flags ^= 1 << 2;
                            break;
                        case SDLK_4:
                            debug_flags ^= 1 << 3;
                            break;
                        case SDLK_5:
                            debug_flags ^= 1 << 4;
                            break;
                        case SDLK_6:
                            debug_flags ^= 1 << 5;
                            break;
                        case SDLK_7:
                            debug_flags ^= 1 << 6;
                            break;
                        case SDLK_8:
                            debug_flags ^= 1 << 7;
                            break;
                        case SDLK_9:
                            debug_flags ^= 1 << 8;
                            break;
                        case SDLK_q:
                            debug_flags ^= 1 << 9;
                            break;
                        case SDLK_w:
                            debug_flags ^= 1 << 10;
                            break;
                        case SDLK_e:
                            debug_flags ^= 1 << 11;
                            break;
                    }
#else
                    user.keyEvent(key);
#endif
                    break;
                }
            }
        }

        drawObj.setRotate(vec3d{ t, 0, -t });
        auto vst_list = VertexShader::vertexing(&drawObj, &user);
        for (auto& vst : vst_list)
            vst.initTangentLight(light);

        std::vector<Fragment> fragments = Rasterizer::rasterize(win, vst_list);
#ifndef NDEBUG
        t = 0;
        for (int i = 0; i < 12; i++)
            if (debug_flags & (1 << i))
                fragments[i].is_culled = true;
#endif
        fragments = fs.lighting(fragments, &drawObj.texture);

        t += 1;

        win->render(fragments);

        win->update();
        SDL_RenderPresent(win->_renderer);
    }
    delete win;

    return 0;
}
