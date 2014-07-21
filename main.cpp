#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "game.h"
#include "painter.h"
#include "menu.h"

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

	if(TTF_Init() == -1) {
		std::cout << "SDL_ttf cou not initialize! SDL_ttf error:  " << TTF_GetError() << std::endl;
	}

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
	painter->initFonts();

	bool gameIsStarted = false;

	Game game(painter);
	Menu mainMenu(listener);

	mainMenu.addItem("New game");

	// game.loadLevel();
	// game.setEventListener(listener);

	while(!listener->isQuit()) {
		listener->listen();

		if(gameIsStarted)
			game.frame();
		else {
			mainMenu.frame();
			int commandId = -1;
			commandId = mainMenu.getItemId();
			if(commandId == 0) {
				gameIsStarted = true;
				game.loadLevel();
				game.setEventListener(listener);
			}
		}

		painter->clear();

		if(gameIsStarted)
			game.render();
		else
			mainMenu.draw(painter);

		painter->present();
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	delete listener;
	delete painter;

	return 0;
}
