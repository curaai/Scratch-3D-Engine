#include "IDrawable.h"
#include "window.h"

#include <ctime>

constexpr uint w=480;
constexpr uint h=480;


using namespace std;

void f() {
  clock_t begin = clock();


  clock_t end = clock();
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
}

int main(int argc, char* argv[])
{
    std::vector<triangle> triangles = {
        // SOUTH
		{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f },

		// EAST                                                      
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f },

		// NORTH                                                     
		{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f },

		// WEST                                                      
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f },

		// TOP                                                       
		{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f },

		// BOTTOM                                                    
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
    };

	mesh cube {triangles};

    Drawable drawObj { cube };
    drawObj.setScale(0.5f * w, 0.5 * h, 1);
    drawObj.setRotate(0, 0, 0);
    drawObj.setTranslate(0, 0, 3.0f);
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
        fTheta = 2.0f * double(curTime - begin) / CLOCKS_PER_SEC ;
        drawObj.setRotate(fTheta, 0, fTheta);

		win->update();
		win->render(drawObj);
		SDL_RenderPresent(win->_renderer);
	}
	delete win;

	return 0;
}
