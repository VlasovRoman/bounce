#ifndef SPIKE
#define SPIKE

#include "gameObject.h"

class Spike : public GameObject {

public:
	Spike();

	void 		initBody(b2World* world, float x, float y);
};

#endif