#ifndef DRAWABLE
#define DRAWABLE

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "dynamicBody.h"

enum OBJECT_TYPE {
	NONE,
	BLOCK,
	BALL,
	GOAL,
	PIN,
	SPIDER,
	LIF,
	CHECK,
	WATER,
	END_LEVEL,
	PUMP_TO_BIG,
	PUMP_TO_SMALL,
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