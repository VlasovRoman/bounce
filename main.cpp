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
	bool quit = false;

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

	mainMenu.addItem("New game", true);
	mainMenu.addItem("Continue", false);
	mainMenu.addItem("Quit", true);

	mainMenu.init();

	// game.loadLevel();
	// game.setEventListener(listener);

	while(!quit || !listener->isQuit()) {
		listener->listen();

		if(gameIsStarted) {
			if(listener->isKeyDown(KEY_ESCAPE)) {
				cout << "escape.." << endl;
				gameIsStarted = false;
			}
			else
				game.frame();
		}
		else {
			mainMenu.frame();
			if(mainMenu.isItemPressed("New game")) {
				gameIsStarted = true;
				game.loadLevel();
				game.setEventListener(listener);
			}
			if(mainMenu.isItemPressed("Quit")) {
				quit = true;
				cout << "quit..." << endl;
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
