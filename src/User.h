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

enum class EUserMove
{
    LEFT = SDLK_LEFT,
    RIGHT = SDLK_RIGHT,
    FORWARD = SDLK_UP,
    BACKWARD = SDLK_DOWN
};

enum class EUserTurn
{
    LEFT = SDLK_a,
    RIGHT = SDLK_d,
    UP = SDLK_w,
    DOWN = SDLK_s
};

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
            move(static_cast<EUserMove>(key));
        else if (rotate_keys.find(key) != rotate_keys.end())
            turn(static_cast<EUserTurn>(key));
    }
    void move(EUserMove key)
    {
        vec3d move_vec;
        switch (key) {
            case EUserMove::LEFT:
                move_vec = vec3d{ -move_speed, 0, 0 };
                break;
            case EUserMove::RIGHT:
                move_vec = vec3d{ move_speed, 0, 0 };
                break;
            case EUserMove::FORWARD:
                move_vec = vec3d{ 0, 0, move_speed };
                break;
            case EUserMove::BACKWARD:
                move_vec = vec3d{ 0, 0, -move_speed };
                break;
        }
        auto rotate_mat = util::mat::GetRotationMat(rotation);
        setCameraPos(pos + rotate_mat * move_vec);
    }
    void turn(EUserTurn key)
    {
        vec3d rotate_vec;
        switch (key) {
            case EUserTurn::LEFT:
                rotate_vec = vec3d{ 0, -turn_speed, 0 };
                break;
            case EUserTurn::RIGHT:
                rotate_vec = vec3d{ 0, turn_speed, 0 };
                break;
            case EUserTurn::UP:
                rotate_vec = vec3d{ -turn_speed, 0, 0 };
                break;
            case EUserTurn::DOWN:
                rotate_vec = vec3d{ turn_speed, 0, 0 };
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

    float move_speed = 0.5;
    float turn_speed = 5;
};