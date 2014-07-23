#ifndef ARROW
#define ARROW

#include "gameObject.h"

enum ARROW_TYPE {
	AT_UP,
	AT_RIGHT,
	AT_DOWN,
	AT_LEFT
};

class Arrow : public GameObject {
	ARROW_TYPE	type;

public:
	Arrow();
	Arrow(ARROW_TYPE type);

	ARROW_TYPE	getType();

	void 		initBody(b2World* world, float x, float y);
};

#endif
