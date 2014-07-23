#include "gui.h"
#include <SDL2/SDL_image.h>

Gui::Gui(Painter* painter) {
	this->painter = painter;
}

void Gui::draw(Player *player, int ringsNumber) {
	painter->drawGuiBase(0, 32 * 8);

	int lives = player->getLives();

	for(int i = 0; i < lives; i++) {
		painter->drawGuiLive(12 + i * 25, 32 * 8 + 5);
	}

	for(int i = 0; i < ringsNumber; i++) {
		painter->drawGuiRing(12 + i * 25, 32 * 9 + 5);
	}
}