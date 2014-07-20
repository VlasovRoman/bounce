#ifndef RING
#define RING

#include <SDL2/SDL.h>

#include "gameObject.h"
#include "sprite.h"
#include "camera.h"

#include "gameObject.h"

enum RING_PART {
	LEFT,
	RIGHT
};

enum RING_TYPE {
	BIG,
	SMALL
};

enum RING_ORIENTATION {
	VERTICALE,
	HORIZONTALE
};

class Ring : public GameObject, public Sprite {
protected:
	SDL_Texture*		onTextureRight;
	SDL_Texture*		offTextureRight;
	SDL_Texture*		onTextureLeft;
	SDL_Texture*		offTextureLeft;
	b2Body*				firstBody;
	b2Body*				secondBody;
	b2BodyDef			firstBodyDef;
	b2BodyDef			secondBodyDef;

	RING_TYPE			type;
	RING_ORIENTATION	orientation;
	Camera*				camera;
	bool				active;
public:
	Ring(SDL_Renderer* renderer, Camera* camera);

	void			init(RING_ORIENTATION orientation, RING_TYPE type);
	void 			setOnTexture(SDL_Texture* right, SDL_Texture* left);
	void 			setOffTexture(SDL_Texture* right, SDL_Texture* left);

	void 			initBody(b2World* world, float x, float y);

	RING_ORIENTATION	getOrientation();

	bool			isActive();
	void 			diactivate();

	void 			draw(RING_PART part);
};

#endif