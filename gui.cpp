#include "gui.h"
#include <SDL2/SDL_image.h>

Gui::Gui() {
	renderer = NULL;

}

Gui::Gui(SDL_Renderer* renderer) {
	this->renderer = renderer;
	lives = 0;
}

void Gui::initSprites() {
	base = new Sprite(renderer);
	base->loadTexture("resources/guiBase.png");

	life = new Sprite(renderer);
	life->loadTexture("resources/guiLife.png");

	ring = new Sprite(renderer);
	ring->loadTexture("resources/guiRing.png");
}

void Gui::setPlayer(Player *player) {
	this->player = player;
}

void Gui::setRingsNumber(int* number) {
	// activeRings = number;
}

void Gui::draw(Player *player, int ringsNumber) {
	base->draw(0, 32 * 8);

	lives = player->getLives();

	for(int i = 0; i < lives; i++) {
		life->draw(12 + i * 25, 32 * 8 + 5);
	}

	for(int i = 0; i < ringsNumber; i++) {
		ring->draw(12 + i * 25, 32 * 9 + 5);
	}
}