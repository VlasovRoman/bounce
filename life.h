#ifndef LIFE
#define LIFE

#include "gameObject.h"
#include "iDrawable.h"

class Life : public GameObject, public iDrawable {
protected:
	bool				deleted;
public:
	Life();

	void 			initBody(b2World* world, float x, float y);

	void 			setDelete();
	bool			isDeleted();

	void 			draw(Painter* painter);
};

#endif