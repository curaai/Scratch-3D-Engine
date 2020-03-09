// Doom-engine.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "window.h"
#include "RelativeWindow.h"
#include "world.h"
#include "user.h"
#include "wall.h"
#include "bean.h"

#include <iostream>
#include <SDL.h>

#define MAIN_MAP_W 1280
#define MAIN_MAP_H 640

int main(int argc, char* argv[])
{
	User* user = new User(300, 300, rgba {255, 255, 0, 255});
	auto win = new RelativeWindow("2d", MAIN_MAP_W, MAIN_MAP_H, user);
	auto world = new World();
	Wall* wall1 = new Wall(Point{100, 100}, Point{400, 100}, rgba{255, 0, 0, 255});
	// Wall* wall2 = new Wall(Point{50, 50}, Point{400, 400}, rgba{0, 0, 255, 255});

	world->addElement(wall1);
	// world->addElement(wall2);

	SDL_Keycode key;
	SDL_Event event;
	while (win->running()) {
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

		win->update();
		win->render(world->getElements());
	}
	delete win;

	return 0;
}
