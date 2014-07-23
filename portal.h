#ifndef PORTAL
#define PORTAL

#include "gameObject.h"
// #include "camera.h"
#include "iDrawable.h"

class Portal : public GameObject, public iDrawable {
	bool 				active;
public:
	Portal();

	void 			initBody(b2World* world, float x, float y);
	
	void 			setActive();
	bool			getState();

	void 			draw(Painter* painter);
};

#endif