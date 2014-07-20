#include "sprite.h"
#include <SDL2/SDL_image.h>
#include <iostream>

using namespace std;

Sprite::Sprite(SDL_Renderer* renderer) {
	this->renderer = renderer;
	this->texture = NULL;
}

Sprite::~Sprite() {
	renderer = NULL;
	texture = NULL;
}

void Sprite::setTexture(SDL_Texture* texture) {
	this->texture = texture;
	//checking...
}

void Sprite::drawTexture(float x, float y) {
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopy(renderer, texture, NULL, &pos);
}

void Sprite::draw(float x, float y) {
	drawTexture(x, y);
}

void Sprite::loadTexture(std::string name) {
	if(texture != NULL) {
		texture = NULL;
	}

	texture = IMG_LoadTexture(renderer, name.c_str());
	if(texture == NULL)
		std::cout << SDL_GetError() << std::endl;
}