#ifndef WALL
#define WALL

#include "gameObject.h"

enum BLOCK_TYPE {
	SOLID,
	DOWN_RIGHT_EDGE,
	DOWN_LEFT_EDGE,
	UP_RIGHT_EDGE,
	UP_LEFT_EDGE
};

class Wall : public GameObject {
	BLOCK_TYPE	type;

	bool 		jumpWall;

public:
	Wall();
	Wall(BLOCK_TYPE type, bool jumpWall = false);

	void 		initBody(b2World* world, float x, float y);

	bool 		isJumpWall();
};

#endif