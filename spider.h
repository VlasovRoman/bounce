#ifndef SPIDER
#define SPIDER

#include "gameObject.h"
#include "iDrawable.h"
// #include "painter.h"

struct SPIDER_DIRECTION {
	int  deltaX;;
	int  deltaY;
};

// class SpiderDirectionObject : public GameObject, public iDrawable {
// 	SPIDER_DIRECTION	direction;
// public:
// 	SpiderDirectionObject(int directionId);
// };

class Spider: public GameObject, public iDrawable {
protected:
	float 				velocity;
	// b2Vec2				motion;

	// bool				isWhole;

	// bool*				isRightPart;

	SPIDER_DIRECTION	direction;
	// bool				up;
	// bool				right;

	// bool 				alreadyChecked;

	void			setDirection(int x, int y);
public:
	Spider();
	Spider(Painter* painter);

	// void 			setWhole(bool is, bool isRight = false);
	void 			initBody(b2World* world, float x, float y);
	
	void 			frame();

	// void 			setAlreadyChecked(bool is);
	// bool 			isAlreadyChecked();
	void 			setDirection(int directonId);
	// void			reverse();

	void 			draw(Painter* painter);
};

#endif
 