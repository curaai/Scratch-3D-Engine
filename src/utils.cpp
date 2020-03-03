#include "utils.h"
#include "bean.h"

#include <SDL.h>
#include <string>


namespace util {
    namespace str {
        using namespace std;

        string trim(string& s, const string& drop)
        {
            string r=s.erase(s.find_last_not_of(drop)+1);
            return r.erase(0, r.find_first_not_of(drop));
        }
        vector<string> split(const string& s, const char delim)
        {
            vector<string> result;
            stringstream ss (s);
            string item;

            while (getline (ss, item, delim)) {
                result.push_back (item);
            }

            return result;
        }
    }
    namespace sdl {
        void set_pixel(SDL_Renderer *rend, int x, int y, rgba c)
        {
            SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
            SDL_RenderDrawPoint(rend, x, y);
            SDL_SetRenderDrawColor(rend, 0,0,0,255);
        }
        void draw_circle(SDL_Renderer *rend, int n_cx, int n_cy, int radius, rgba c, bool fill)
        {
            double error = (double)-radius;
            double x = (double)radius - 0.5;
            double y = (double)0.5;
            double cx = n_cx - 0.5;
            double cy = n_cy - 0.5;

            int drawX, drawY;
            auto drawPixels = [&](int x, int y) {
                set_pixel(rend, x, y, c);
                set_pixel(rend, y, x, c);
                set_pixel(rend, x, -y, c);
                set_pixel(rend, y, -x, c);
                set_pixel(rend, -x, y, c);
                set_pixel(rend, -y, x, c);
                set_pixel(rend, -x, -y, c);
                set_pixel(rend, -y, -x, c);
            };

            while (x >= y)
            {
                drawPixels(cx+x, cy+y);

                error += y;
                ++y;
                error += y;

                if (error >= 0)
                {
                    --x;
                    error -= x;
                    error -= x;
                }
            }
            if (fill)
                fill_circle(rend, cx, cy, radius, c);
        }
        // can be optimize with join boundary pixels
        // now using float-operation
        void fill_circle(SDL_Renderer *rend, int cx, int cy, int radius, rgba c)
        {
            for (double dy = 1; dy <= radius; dy += 1.0)
            {
                double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
                int x = cx - dx;
                SDL_SetRenderDrawColor(rend, c.r, c.g, c.b, c.a);
                SDL_RenderDrawLine(rend, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
                SDL_RenderDrawLine(rend, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);
                SDL_SetRenderDrawColor(rend, 0,0,0,255);
            }
        }
    }
}
