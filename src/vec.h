#pragma once

#include <iostream>
#include <math.h>

#define TO_RADIAN(x) x* M_PI / 180

struct vec2d
{
    float x, y;
    vec2d(float x = 0, float y = 0)
        : x(x)
        , y(y)
    {}
    inline vec2d operator+(const vec2d v) const { return vec2d{ *this } += v; }
    inline vec2d& operator+=(const vec2d v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    inline vec2d operator-(const vec2d v) const { return vec2d{ *this } -= v; }
    inline vec2d& operator-=(const vec2d v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    inline vec2d operator*(const vec2d v) const { return vec2d{ *this } *= v; }
    inline vec2d& operator*=(const vec2d v)
    {
        x *= v.x;
        y *= v.y;
        return *this;
    }
    inline vec2d operator/(const vec2d v) const { return vec2d{ *this } /= v; }
    inline vec2d& operator/=(const vec2d v)
    {
        x /= v.x;
        y /= v.y;
        return *this;
    }
    inline vec2d& operator+=(const float v)
    {
        x += v;
        y += v;
        return *this;
    }
    inline vec2d operator+(const float a) const { return vec2d{ *this } += a; }
    inline vec2d& operator-=(const float v)
    {
        x -= v;
        y -= v;
        return *this;
    }
    inline vec2d operator-(const float a) const { return vec2d{ *this } -= a; }
    inline vec2d& operator*=(const float v)
    {
        x *= v;
        y *= v;
        return *this;
    }
    inline vec2d operator*(const float a) const { return vec2d{ *this } *= a; }
    inline vec2d& operator/=(const float v)
    {
        x /= v;
        y /= v;
        return *this;
    }
    inline vec2d operator/(const float a) const { return vec2d{ *this } /= a; }
    inline vec2d operator-(void) const { return vec2d{ -x, -y }; }
    inline float length(void) const { return sqrt(x * x + y * y); }
    inline vec2d normalize(void) const { return *this / length(); }

    friend std::ostream& operator<<(std::ostream& os, const vec2d& vec)
    {
        os << vec.x << ' ' << vec.y << std::endl;
        return os;
    }
};

struct vec3d : vec2d
{
    float z;
    vec3d(float x = 0, float y = 0, float z = 0)
        : vec2d(x, y)
        , z(z)
    {}
    inline vec3d operator+(const vec3d v) const { return vec3d{ *this } += v; }
    inline vec3d& operator+=(const vec3d v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    inline vec3d operator-(const vec3d v) const { return vec3d{ *this } -= v; }
    inline vec3d& operator-=(const vec3d v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    inline vec3d operator*(const vec3d v) const { return vec3d{ *this } *= v; }
    inline vec3d& operator*=(const vec3d v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        return *this;
    }
    inline vec3d operator/(const vec3d v) const { return vec3d{ *this } /= v; }
    inline vec3d& operator/=(const vec3d v)
    {
        x /= v.x;
        y /= v.y;
        z /= v.z;
        return *this;
    }
    inline vec3d operator+(const float a) const { return vec3d{ *this } += a; }
    inline vec3d& operator+=(const float a)
    {
        x += a;
        y += a;
        z += a;
        return *this;
    }
    inline vec3d operator-(const float a) const { return vec3d{ *this } -= a; }
    inline vec3d& operator-=(const float a)
    {
        x -= a;
        y -= a;
        z -= a;
        return *this;
    }
    inline vec3d operator*(const float a) const { return vec3d{ *this } *= a; }
    inline vec3d& operator*=(const float a)
    {
        x *= a;
        y *= a;
        z *= a;
        return *this;
    }
    inline vec3d operator/(const float a) const { return vec3d{ *this } /= a; }
    inline vec3d& operator/=(const float a)
    {
        x /= a;
        y /= a;
        z /= a;
        return *this;
    }
    inline vec3d operator-(void) const { return vec3d{ -x, -y, -z }; }
    inline bool operator==(const vec3d& v) const
    {
        return v.x == x && v.y == y && v.z == z;
    }
    inline float length(void) const { return sqrt(x * x + y * y + z * z); }
    inline vec3d normalize(void) const { return *this / length(); }

    friend std::ostream& operator<<(std::ostream& os, const vec3d& vec)
    {
        os << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;
        return os;
    }
};