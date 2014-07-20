#ifndef LIFE
#define LIFE

#include "gameObject.h"
#include "sprite.h"

class Life : public GameObject, public Sprite {
protected:
	bool				deleted;
public:
	Life(Painter* painter);

	void 			initBody(b2World* world, float x, float y);

	void 			setDelete();
	bool			isDeleted();

	void 			draw();
};

#endif