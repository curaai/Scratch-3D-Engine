#include "IDrawable.h"
#include "window.h"

#include <ctime>

constexpr uint w=640;
constexpr uint h=480;


using namespace std;

void f() {
  clock_t begin = clock();


  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[])
{
    // draw cube
	std::vector<vec3d> pts = {
		{0, 0, 0}, {1, 0, 0},
		{0, 0, 1}, {1, 0, 1},
		{0, 1, 0}, {1, 1, 0},
		{0, 1, 1}, {1, 1, 1},
	};
    
    std::vector<vecIdx> idxArr = {
        {0, 4, 5}, {0, 5, 1}, // south
        {1, 5, 7}, {1, 7, 3}, // east
        {3, 7, 6}, {3, 6, 2}, // north
        {2, 6, 4}, {2, 4, 0}, // west
        {4, 6, 7}, {4, 7, 5}, // top
        {3, 2, 0}, {3, 0, 1}, // bottom
    };

	mesh cube {pts, idxArr};
    Drawable drawObj { cube };
    drawObj.setScale(0.5f * w, 0.5 * h, 1);
    drawObj.setRotate(0, 0, 0);
    drawObj.setTranslate(1.0f, 1.0f, 3.0f);
    drawObj.setProjection((float)h/(float)w, 90.0f, 1000.0f, 0.1f);
	
    Window* win = new Window {"3D engine", w, h};

    float fTheta;

    clock_t begin = clock();
    SDL_Keycode key;
	SDL_Event event;
	while (win->running()) {
		while(SDL_PollEvent(&event))
		{
			switch(event.type) 
			{
			case SDL_QUIT:
                win->isRunning = false;
				break;
			}
		}

        clock_t curTime = clock();
        fTheta = 1.0f * double(curTime - begin) / CLOCKS_PER_SEC ;
        drawObj.setRotate(fTheta, 0, fTheta);

		win->update();
		win->render(drawObj);
		SDL_RenderPresent(win->_renderer);
	}
	delete win;

	return 0;
}
