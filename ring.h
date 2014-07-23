#ifndef RING
#define RING

#include "gameObject.h"
#include "iDrawable.h"
#include "painter.h"

// enum RING_PART {
// 	LEFT,
// 	RIGHT
// };

// enum RING_SIZE {
// 	BIG,
// 	SMALL
// };

// enum RING_ORIENTATION {
// 	VERTICALE,
// 	HORIZONTALE
// };

class Ring : public GameObject, public iDrawable {
protected:
	// b2Body*				firstBody;
	// b2Body*				secondBody;
	// b2BodyDef			firstBodyDef;
	// b2BodyDef			secondBodyDef;

	b2Vec2*				playerPosition;
	b2Vec2				lastDelta;

	// RING_SIZE			type;
	// RING_ORIENTATION	orientation;
	// b2Vec2				lastPlayerShift;

	bool 				isBig;
	bool				isVert;
	bool				active;
public:
	Ring();

	void			init(bool isVert, bool isBig);
	void 			initBody(b2World* world, float x, float y);

	// bool			isPlayerShiftChanged(b2Vec2 playerPosition);

	bool			getOrientation();

	bool			getBig();

	void 			setPlayerPosition(b2Vec2* position);
	void 			checkOnThePassage();
	bool			isActive();
	void 			diactivate();

	void 			draw(Painter* painter, bool drawRightPart);
	void 			draw(Painter* painter);
};

#endif