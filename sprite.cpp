#include "sprite.h"

Sprite::Sprite(Painter* painter) {
	this->painter = painter;
}

Sprite::~Sprite() {
	painter = NULL;
}