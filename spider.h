#ifndef SPIDER
#define SPIDER

#include "gameObject.h"
#include "iDrawable.h"

struct SPIDER_DIRECTION {
	int  deltaX;;
	int  deltaY;
};

class Spider: public GameObject, public iDrawable {
protected:
	float 				velocity;

	SPIDER_DIRECTION	direction;

	void				setDirection(int x, int y);
public:
	Spider();
	Spider(Painter* painter);

	void 			initBody(b2World* world, float x, float y);
	
	void 			frame();

	void 			setDirection(int directonId);

	void 			draw(Painter* painter);
};

#endif
 