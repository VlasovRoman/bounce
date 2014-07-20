#ifndef BONUS
#define BONUS

#include "gameObject.h"

enum BONUS_TYPE {
	BT_SPEED,
	BT_ANTIGRAVITATION,
	BT_JUMPING
};

class Bonus : public GameObject {
	BONUS_TYPE	type;

public:
	Bonus();
	Bonus(BONUS_TYPE type);

	void 		initBody(b2World* world, float x, float y);
	BONUS_TYPE	getType();
};

#endif