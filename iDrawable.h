#ifndef SPRITE
#define SPRITE

#include "painter.h"

struct iDrawable {
// protected:
// 	Painter*		painter;
// public:
// 	Sprite(Painter* painter = NULL);
// 	virtual ~Sprite();

	virtual	void draw(Painter* painter) = 0;
};

#endif