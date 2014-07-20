#ifndef LIFE
#define LIFE

#include <SDL2/SDL.h>

#include "gameObject.h"
#include "eventListener.h"
#include "sprite.h"
#include "camera.h"

#include "gameObject.h"

class Life : public GameObject, public Sprite {
protected:
	Camera*				camera;

	bool				deleted;
public:
	Life(SDL_Renderer* renderer, Camera* camera);

	void 			initBody(b2World* world, float x, float y);

	void 			setDelete();
	bool			isDeleted();

	void 			draw();
};

#endif