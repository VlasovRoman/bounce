#ifndef EVENT_LISTENER
#define EVENT_LISTENER

#include <SDL2/SDL.h>

#include <iostream>

enum KEY_NAME {
	KEY_UP,
	KEY_LEFT,
	KEY_RIGHT
};

class EventListener {
	SDL_Event* 		event;

	bool			keyUp;
	bool 			keyDown;
	bool			keyLeft;
	bool			keyRight;

	void clearStatus() {
		keyUp = false;
		keyLeft = false;
		keyRight = false;
	}

public:
	EventListener() {
		event = new SDL_Event();
		clearStatus();
	}

	void listen() {

		clearStatus();
		SDL_PollEvent(event);
		if(event->type == SDL_KEYDOWN) {
			switch(event->key.keysym.sym) {
				case SDLK_LEFT:
					keyLeft = true;
					break;
				case SDLK_RIGHT:
					keyRight = true;
					break;
				case SDLK_UP:
					keyUp = true;
					break;
			} 
		}
	}

	bool 			isQuit() {
		if(event->type == SDL_QUIT) {
			return true;
		}
		else 
			return false;
	}

	bool	isKeyDown(KEY_NAME name) {
		if(name == KEY_LEFT) {
			return keyLeft;
		}
		if(name == KEY_RIGHT) {
			return keyRight;
		}
		if(name == KEY_UP) {
			return keyUp;
		}
		else
			return false;
	}
};

#endif