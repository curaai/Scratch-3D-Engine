#pragma once 

#include <math.h>
#include <cmath>
#include <cstdint>

typedef struct rgba
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
} rgba;

typedef struct Point
{
    float x;
    float y;

    Point operator+(const Point& a) const 
    {
        float _x = x + a.x;
        float _y = y + a.y;
        return Point{_x, _y};
    }
    Point operator-(const Point& a) const 
    {
        float _x = x - a.x;
        float _y = y - a.y;
        return Point{_x, _y};
    }
    Point rotation(float degree) const 
    {
        float ori = (degree* M_PI ) / 180;
        float newx = cos(ori) * x - sin(ori) * y;
        float newy = sin(ori) * x - cos(ori) * y;
        return Point{newx, newy};
    }
    float eucDist(const Point& pt) const 
    {
        return std::sqrt(std::pow(pt.x - x, 2) + std::pow(pt.y - y, 2));
    }
    float manDist(const Point& pt) const 
    {
        return std::abs(pt.x - x) + std::abs(pt.y - y);
    }
} Point;