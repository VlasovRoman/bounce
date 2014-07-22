#ifndef EVENT_LISTENER
#define EVENT_LISTENER

#include <SDL2/SDL.h>

#include <iostream>

enum KEY_NAME {
	KEY_UP,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_DOWN,
	KEY_ENTER, 
	KEY_ESCAPE
};

enum ListenerStatus {
	LS_GAME,
	LS_MENU
};

class EventListener {
	SDL_Event* 		event;
	ListenerStatus	status;

	int count;
	int countPause ;

	bool			keyUp;
	bool 			keyDown;
	bool			keyLeft;
	bool			keyRight;
	bool 			keyEnter;

	bool			keyEscape;


public:
	void clearStatus() {
		keyUp = false;
		keyLeft = false;
		keyRight = false;
		keyDown = false;
		keyEnter = false;
		keyEscape = false;
	}
	EventListener() {
		event = new SDL_Event();
		clearStatus();
		count = 0;
		countPause = 4;
	}

	void setStatus(ListenerStatus _status) {
		status = _status;
	}

	void listen() {

		clearStatus();
		SDL_PollEvent(event);
		if(count == 0 || status == LS_GAME) {
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
					case SDLK_DOWN:
						keyDown = true;
						break;
					case SDLK_RETURN:
						keyEnter = true;
						break;
					case SDLK_ESCAPE:
						keyEscape = true;
						break;
				} 
			}

			if(status == LS_MENU) {
				count = 4;
			}
		}
		else {
			count--;
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
		// if(name == KEY_LEFT) {
		// 	return keyLeft;
		// }
		// if(name == KEY_RIGHT) {
		// 	return keyRight;
		// }
		// if(name == KEY_UP) {
		// 	return keyUp;
		// }
		// if(name == KEY_DOWN)
		// 	return keyDown;
		// if(name == KEY_ENTER) {
		// 	bool dd = keyEnter;
		// 	keyEnter = false;
		// 	return dd;
		// }
		// if(name == KEY_ESCAPE) {
		// 	return keyEscape;
		// }
		// else
		// 	return false;
			switch(name) {
				case KEY_ENTER: {
					return keyEnter;
				} break;
				case KEY_ESCAPE: {
					return keyEscape;
				} break;
				case KEY_UP: {
					return keyUp;
				} break;
				case KEY_RIGHT: {
					return keyRight;
				} break;
				case KEY_DOWN: {
					return keyDown;
				} break;
				case KEY_LEFT: {
					return keyLeft;
				} break;

			}

	}




};

#endif