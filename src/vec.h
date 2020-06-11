#pragma once

#include <iostream>
#include <math.h>

template<int N>
struct vec
{
    float coords[N] = { 0 };

    inline vec<N> operator+(const vec<N>& v) const
    {
        return vec<N>{ *this } += v;
    }
    inline vec<N> operator-(const vec<N>& v) const
    {
        return vec<N>{ *this } -= v;
    }
    inline vec<N> operator*(const vec<N>& v) const
    {
        return vec<N>{ *this } *= v;
    }
    inline vec<N> operator/(const vec<N>& v) const
    {
        return vec<N>{ *this } /= v;
    }
    inline vec<N> operator+(const float a) const
    {
        return vec<N>{ *this } += a;
    }
    inline vec<N> operator-(const float a) const
    {
        return vec<N>{ *this } -= a;
    }
    inline vec<N> operator*(const float a) const
    {
        return vec<N>{ *this } *= a;
    }
    inline vec<N> operator/(const float a) const
    {
        return vec<N>{ *this } /= a;
    }
    inline vec<N>& operator+=(const vec<N>& v)
    {
        for (unsigned char i = 0; i < N; i++)
            coords[i] += v.coords[i];
        return *this;
    }
    inline vec<N>& operator-=(const vec<N>& v)
    {
        for (unsigned char i = 0; i < N; i++)
            coords[i] -= v.coords[i];
        return *this;
    }
    inline vec<N>& operator*=(const vec<N>& v)
    {
        for (unsigned char i = 0; i < N; i++)
            coords[i] *= v.coords[i];
        return *this;
    }
    inline vec<N>& operator/=(const vec<N>& v)
    {
        for (unsigned char i = 0; i < N; i++)
            coords[i] /= v.coords[i];
        return *this;
    }
    inline vec<N>& operator+=(float a)
    {
        for (unsigned char i = 0; i < N; i++)
            coords[i] += a;
        return *this;
    }
    inline vec<N>& operator-=(float a)
    {
        for (unsigned char i = 0; i < N; i++)
            coords[i] -= a;
        return *this;
    }
    inline vec<N>& operator*=(float a)
    {
        for (unsigned char i = 0; i < N; i++)
            coords[i] *= a;
        return *this;
    }
    inline vec<N>& operator/=(float a)
    {
        for (unsigned char i = 0; i < N; i++)
            coords[i] /= a;
        return *this;
    }
    inline bool operator==(const vec<N>& v) const
    {
        bool flag = true;
        for (int i = 0; i < N; i++)
            flag &= v[i] == coords[i];
        return flag;
    }
    inline float& operator[](int i) { return coords[i]; }
    inline float operator[](int i) const { return coords[i]; }
    inline vec<N> operator-(void) const
    {
        vec<N> v;
        for (int i = 0; i < N; i++)
            v[i] = -coords[i];

        return v;
    }
    inline float length(void) const
    {
        float sum = 0;
        for (unsigned char i = 0; i < N; i++) {
            sum += coords[i] * coords[i];
        }
        return sqrt(sum);
    }
    inline vec<N> normalize(void) const { return *this / length(); }
    friend std::ostream& operator<<(std::ostream& os, const vec<N>& vec)
    {
        for (unsigned char i = 0; i < N; i++)
            os << vec.coords[i] << ' ';
        return os;
    }

    explicit operator vec<2>(void) const
    {
        vec<2> v;
        v[0] = coords[0];
        v[1] = coords[1];
        return v;
    }
};

using vec2d = vec<2>;
using vec3d = vec<3>;