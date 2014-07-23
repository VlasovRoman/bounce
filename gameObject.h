#ifndef GAME_OBJECT
#define GAME_OBJECT

#include "dynamicBody.h"

enum OBJECT_TYPE {
	NONE,
	BLOCK,
	BALL,
	GOAL,
	PIN,
	PAUK,
	LIF,
	CHECK,
	WTR,
	END_LEVEL,
	PUMPILA,
	BONUSE,
	DIRECTION
};

class GameObject : public iDynamicBody{
protected:
	OBJECT_TYPE		type;
public:
					GameObject(OBJECT_TYPE type);
	virtual 		~GameObject();


	OBJECT_TYPE		getType();
};

#endif