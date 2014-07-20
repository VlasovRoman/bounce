#ifndef PUMP
#define PUMP

#include "gameObject.h"

enum PUMP_TYPE {
	INFLATOR, 
	OUTPUT
};

class Pump : public GameObject {
	PUMP_TYPE	pumpType;

public:
	Pump();
	Pump(PUMP_TYPE type);

	void 		initBody(b2World* world, float x, float y);

	PUMP_TYPE	getPumpType();
};

#endif