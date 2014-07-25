#ifndef SPIKE
#define SPIKE

#include "gameObject.h"

class Spike : public GameObject {
	int 		directionId;

public:
	Spike();

	void 		setDirection(int tileModoficatoinId);

	void 		initBody(b2World* world, float x, float y);
};

#endif