#ifndef PORTAL
#define PORTAL

#include "gameObject.h"
#include "camera.h"
#include "sprite.h"

class Portal : public GameObject, public Sprite {
	bool 				active;
public:
	Portal(Painter* painter);

	void 			initBody(b2World* world, float x, float y);
	
	void 			setActive();
	bool			getState();

	void 			draw();
};

#endif