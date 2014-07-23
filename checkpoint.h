#ifndef CHECKPOINT
#define CHECKPOINT

#include <SDL2/SDL.h>

#include "gameObject.h"
#include "eventListener.h"
#include "iDrawable.h"
#include "camera.h"

#include "gameObject.h"

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