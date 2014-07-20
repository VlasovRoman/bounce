#include "gui.h"
#include <SDL2/SDL_image.h>

Gui::Gui(Painter* painter) {
	this->painter = painter;

}

void Gui::draw(Player *player, int ringsNumber) {
	// base->draw(0, 32 * 8);
	painter->drawGuiBase(0, 32 * 8);

	int lives = player->getLives();

	for(int i = 0; i < lives; i++) {
		// life->draw(12 + i * 25, 32 * 8 + 5);
		painter->drawGuiLive(12 + i * 25, 32 * 8 + 5);
	}

	for(int i = 0; i < ringsNumber; i++) {
		// ring->draw(12 + i * 25, 32 * 9 + 5);
		painter->drawGuiRing(12 + i * 25, 32 * 9 + 5);
	}
}