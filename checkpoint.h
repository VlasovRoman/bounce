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
	SDL_Texture*		onTexture;
	SDL_Texture*		offTexture;
	Camera*				camera;
	bool				active;
public:
	Checkpoint(SDL_Renderer* renderer, Camera* camera);
	void 			setOnTexture(SDL_Texture* texture);
	void 			setOffTexture(SDL_Texture* texture);

	void 			initBody(b2World* world, float x, float y);

	bool			getActive();
	void			setActive(bool active);

	void 			draw();
};

#endif