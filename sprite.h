#ifndef SPRITE
#define SPRITE

#include "painter.h"

class Sprite {
protected:
	Painter*		painter;
public:
	Sprite(Painter* painter = NULL);
	virtual ~Sprite();

	virtual	void draw() = 0;
};

#endif