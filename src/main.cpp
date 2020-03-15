// Doom-engine.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "window.h"
#include "RelativeWindow.h"
#include "world.h"
#include "user.h"
#include "wall.h"
#include "bean.h"
#include "Engine/RayCasting.h"

#include <iostream>
#include <SDL.h>

#define MAIN_MAP_W 1280
#define MAIN_MAP_H 640

int main(int argc, char* argv[])
{
	User* user = new User(160, 160, rgba {255, 255, 0, 255});
	auto win2d = new RelativeWindow("2d", 640, 640, user);
	auto win3d = new RelativeWindow("3d", 640, 640, user);
	// win->relativeMode = false;
	auto world = new World();
	Wall* wall1 = new Wall(Point{0, 0}, Point{0, 600}, rgba{255, 0, 0, 255});
	Wall* wall2 = new Wall(Point{0, 0}, Point{600, 0}, rgba{255, 255, 0, 255});
	Wall* wall3 = new Wall(Point{600, 0}, Point{600, 600}, rgba{0, 255, 0, 255});
	Wall* wall4 = new Wall(Point{0, 600}, Point{600, 600}, rgba{0, 0, 255, 255});
	// Wall* wall2 = new Wall(Point{50, 50}, Point{400, 400}, rgba{0, 0, 255, 255});

	world->addElement(wall1);
	world->addElement(wall2);
	world->addElement(wall3);
	world->addElement(wall4);
	// world->addElement(wall2);

	RayEngine* engine = new RayEngine(*user, *world);

	SDL_Keycode key;
	SDL_Event event;
	while (win2d->running()) {
		while(SDL_PollEvent(&event))
		{
			switch(event.type) 
			{
			case SDL_KEYDOWN:
				key = event.key.keysym.sym;
				switch(key) {
					case SDLK_LEFT:
					case SDLK_RIGHT:
						user->turn(key);
						break; 
					case SDLK_w:
					case SDLK_a:
					case SDLK_d:
					case SDLK_s:
						user->move(key);
						break;
				}
				break;

			case SDL_QUIT:
				break;
			}
		}

		win2d->update();
		win2d->render(world->getElements());
		engine->draw2d(win2d->_renderer);
		SDL_RenderPresent(win2d->_renderer);

		SDL_RenderClear(win3d->_renderer);
		engine->draw3d(win3d->_renderer);
		SDL_RenderPresent(win3d->_renderer);
	}
	delete win2d;
	delete win3d;

	return 0;
}
