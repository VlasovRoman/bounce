#ifndef CHECKPOINT
#define CHECKPOINT

#include "gameObject.h"
#include "iDrawable.h"

class Checkpoint : public GameObject, public iDrawable {
protected:
	bool				active;
public:
	Checkpoint();

	void 			initBody(b2World* world, float x, float y);

	bool			getActive();
	void			setActive(bool active);

	void 			draw(Painter* painter);
};

#endif