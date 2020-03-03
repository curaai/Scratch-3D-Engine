// Doom-engine.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "window.h"

#include <iostream>
#include <SDL.h>

#define MAIN_MAP_W 1280
#define MAIN_MAP_H 640

int main(int argc, char* argv[])
{
	auto win = new Window("2d", MAIN_MAP_W, MAIN_MAP_H);

	while (win->running()) {
		win->handleEvent();
		win->update();
		win->render();
	}
	delete win;

	return 0;
}
