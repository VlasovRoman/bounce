#ifndef WALL
#define WALL

#include "gameObject.h"

class Wall : public GameObject {

public:
	Wall();

	void 		initBody(b2World* world, float x, float y);
};

#endif