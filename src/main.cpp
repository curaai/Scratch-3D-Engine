#include "IDrawable.h"
#include "window.h"
#include "camera.h"

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
		{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f,-1.0f,    1.0f, 1.0f, 0.0f },

		// BOTTOM                                                    
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f },
		{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f },
    };

	mesh cube {triangles};

    Drawable drawObj { cube };
    drawObj.setScale(0.1 * w, 0.1 * h, 1);
    drawObj.setRotate(0, 0, 0);
	drawObj.setTranslate(0, 0, -3.0f);
	auto worldMat = drawObj.getWorldMat();

	Camera cam {vec3d {-1, -1, 5}};

    Window* win = new Window {"3D engine", w, h};

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

		win->update();
		win->render(drawObj.getConverted(worldMat));
		SDL_RenderPresent(win->_renderer);
	}
	delete win;

	return 0;
}
