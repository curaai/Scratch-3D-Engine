#pragma once 

#include "bean.h"

#include <SDL.h>

#include <string>
#include <sstream>
#include <vector>

#define TRIM_SPACE " \t\n\v"

namespace util {
    namespace str {
        using namespace std;
        
        string trim(string& s, const string& drop = TRIM_SPACE);
        vector<string> split(const string& s, const char delim);
    }
    namespace sdl {
        void set_pixel(SDL_Renderer *rend, int x, int y, rgba c);
        void draw_circle(SDL_Renderer *rend, int n_cx, int n_cy, int radius, rgba c, bool fill=false);
        void fill_circle(SDL_Renderer *rend, int cx, int cy, int radius, rgba c);
    }
}

double deg2rad(double deg);
bool getIntersectPoint(const Point& AP1, const Point& AP2, const Point& BP1, const Point& BP2, Point* IP);