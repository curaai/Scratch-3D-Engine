#pragma once 

#include <iostream>
#include <math.h>
 
#define TO_RADIAN(x) x * M_PI / 180


struct vec3d
{
    float x, y, z;

    inline vec3d operator+ (const vec3d v) const {
        return vec3d{x + v.x, y + v.y, z + v.z};
    }
    inline vec3d operator- (const vec3d v) const {
        return vec3d{x - v.x, y - v.y, z - v.z};
    }
    inline vec3d operator* (const vec3d v) const {
        return vec3d{x * v.x, y * v.y, z * v.z};
    }
    inline vec3d operator/ (const vec3d v) const {
        return vec3d{x / v.x, y / v.y, z / v.z};
    }
    inline vec3d operator* (const float a) const {
        return vec3d{x * a, y * a, z * a};
    }
    inline vec3d operator/ (const float a) const {
        return vec3d{x / a, y / a, z / a};
    }
    inline vec3d operator- (void) const {
        return vec3d{-x, -y, -z};
    }
    inline float length(void) const {
        return sqrt(x*x + y*y + z*z);
    }
    inline vec3d normalize(void) const {
        return *this / length();
    }

    friend std::ostream& operator<<(std::ostream& os, const vec3d& vec)
    {
        os << vec.x << ' ' << vec.y << ' ' << vec.z << std::endl;
        return os;
    } 
};