#ifndef RING
#define RING

#include "gameObject.h"
#include "iDrawable.h"

class Ring : public GameObject, public iDrawable {
protected:
	b2Vec2*	playerPosition;
	b2Vec2	lastDelta;

	bool 	isBig;
	bool	isVert;
	bool	active;

	void 			diactivate();
public:
	Ring();

	void			init(bool isVert, bool isBig);
	void 			initBody(b2World* world, float x, float y);

	// bool			getOrientation();
	bool			getBig();

	void 			setPlayerPosition(b2Vec2* position);
	void 			checkOnThePassage();

	bool			isActive();

	void 			draw(Painter* painter, bool drawRightPart);
	void 			draw(Painter* painter);
};

#endif