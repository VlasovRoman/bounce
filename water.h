#ifndef WATER
#define WATER

#include "gameObject.h"

class Water : public GameObject {

public:
	Water();

	void 		initBody(b2World* world, float x, float y);
};

#endif