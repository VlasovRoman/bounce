#include "CollisionDetection.h"

#ifndef H_CLASS_WALL
#define H_CLASS_WALL

class cWall:public cRect
{
public:
	cWall(float _x, float _y):cRect(_x, _y, -16, 16, 16, 16)
	{};
};

#endif H_CLASS_WALL