#pragma once

#include "camera.h"
#include "util_mat.h"
#include <set>

#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
#error Windows_OS
#elif defined(__linux__)
#include <SDL2/SDL.h>
#elif defined(__APPLE__) && defined(__MACH__)
#include "SDL.h"
#endif

class User : public Camera
{
public:
    explicit User(vec3d pos, float aspect_ratio, float fov)
        : Camera(pos, aspect_ratio, fov){};
    ~User(){};

public:
    void keyEvent(SDL_Keycode key)
    {
        if (move_keys.find(key) != move_keys.end())
            move(key);
        else if (rotate_keys.find(key) != rotate_keys.end())
            turn(key);
    }
    void move(SDL_Keycode key)
    {
        vec3d move_vec;
        switch (key) {
            case SDLK_LEFT:
                move_vec = vec3d{ speed, 0, 0 };
                break;
            case SDLK_RIGHT:
                move_vec = vec3d{ -speed, 0, 0 };
                break;
            case SDLK_UP:
                move_vec = vec3d{ 0, 0, speed };
                break;
            case SDLK_DOWN:
                move_vec = vec3d{ 0, 0, -speed };
                break;
        }
        auto rotate_mat = util::mat::GetRotationMat(rotation);
        setCameraPos(pos + rotate_mat * move_vec);
    }
    void turn(SDL_Keycode key)
    {
        vec3d rotate_vec;
        switch (key) {
            case SDLK_a:
                rotate_vec = vec3d{ 0, 5, 0 };
                break;
            case SDLK_d:
                rotate_vec = vec3d{ 0, -5, 0 };
                break;
            case SDLK_w:
                rotate_vec = vec3d{ -5, 0, 0 };
                break;
            case SDLK_s:
                rotate_vec = vec3d{ 5, 0, 0 };
                break;
            default:
                break;
        }
        setCameraRotation(rotation + rotate_vec);
    }

    const std::set<SDL_Keycode> move_keys{
        SDLK_LEFT,
        SDLK_RIGHT,
        SDLK_UP,
        SDLK_DOWN,
    };
    const std::set<SDL_Keycode> rotate_keys{
        SDLK_a,
        SDLK_d,
        SDLK_w,
        SDLK_s,
    };

    float speed = 0.5;
};