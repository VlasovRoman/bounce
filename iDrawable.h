#ifndef INTERFACE_DRAWABLE
#define INTERFACE_DRAWABLE

#include "painter.h"

struct iDrawable {
	virtual	void draw(Painter* painter) = 0;
};

#endif