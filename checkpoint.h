#ifndef CHECKPOINT
#define CHECKPOINT

#include <SDL2/SDL.h>

#include "gameObject.h"
#include "eventListener.h"
#include "sprite.h"
#include "camera.h"

#include "gameObject.h"

class Checkpoint : public GameObject, public Sprite {
protected:
	bool				active;
public:
	Checkpoint(Painter* painter);

	void 			initBody(b2World* world, float x, float y);

	bool			getActive();
	void			setActive(bool active);

	void 			draw();
};

#endif