#ifndef PORTAL
#define PORTAL

#include "gameObject.h"
#include "camera.h"
#include "sprite.h"

class Portal : public GameObject, public Sprite {
	SDL_Texture*		lockedTexture;
	SDL_Texture*		activeTexture;
	Camera*				camera;

	bool 				active;
public:
	Portal(SDL_Renderer* renderer, Camera* camera);

	void 			initBody(b2World* world, float x, float y);
	
	void 			setActive();
	bool			getState();

	void 			setActiveTexture(SDL_Texture* texture);
	void 			setLockedTexture(SDL_Texture* texture);

	void 			draw();
};

#endif