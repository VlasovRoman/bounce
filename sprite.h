#ifndef SPRITE
#define SPRITE

#include <SDL2/SDL.h>
#include <iostream>
#include "camera.h"

class Sprite {
protected:
	SDL_Texture* 	texture;
	SDL_Renderer*	renderer;

	void 			drawTexture(float x, float y);
public:
	///API 1
	Sprite(SDL_Renderer* renderer = NULL);
	virtual ~Sprite();

	virtual void 	setTexture(SDL_Texture* texture);

	void 			draw(float x, float y);
	///API 2
	void 			loadTexture(std::string name);
};

#endif