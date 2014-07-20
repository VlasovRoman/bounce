#include <iostream>

#include "ResInit.h"
#include "game.h"

Game game;

bool frameFunc() {
	game.frame();

	return false;
}

bool renderFunc(SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);

	game.render();

	SDL_RenderPresent(renderer);

	return false;
}

int main() {
	const int SCREENWIDTH = 320;
	const int SCREENHEIGHT = 64 + 32 * 8;

	bool quit = false;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = NULL;

	window = SDL_CreateWindow("Bounce: Remake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if(window == NULL) {
		std::cout << "Main window could not be initialize! SDL_Error " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer* renderer = NULL;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Event* mainEvent = new SDL_Event();

	EventListener* listener = new EventListener;
	TextureLoad(renderer);
	game = Game(renderer);
	game.loadLevel();
	game.setEventListener(listener);

	while(!quit && !listener->isQuit()) {
		listener->listen();

		frameFunc();
		renderFunc(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;

	return 0;
}
