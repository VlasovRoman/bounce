#include <iostream>

#include <SDL2/SDL.h>

#include "game.h"
#include "painter.h"

// bool frameFunc() {
// 	game.frame();

// 	return false;
// }

// bool renderFunc(Painter* painter)
// {
// 	painter->clear();

// 	game.render();

// 	painter->present();

// 	return false;
// }

int main() {
	const int SCREENWIDTH = 320;
	const int SCREENHEIGHT = 64 + 32 * 8;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = NULL;

	window = SDL_CreateWindow("Bounce: Remake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if(window == NULL) {
		std::cout << "Main window could not be initialize! SDL_Error " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer* renderer = NULL;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	EventListener* listener = new EventListener;

	Painter* painter = new Painter(renderer);
	painter->initTextures();

	Game game(painter);

	game.loadLevel();
	game.setEventListener(listener);

	while(!listener->isQuit()) {
		listener->listen();

		game.frame();

		painter->clear();

		game.render();

		painter->present();
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	delete listener;
	delete painter;

	return 0;
}
