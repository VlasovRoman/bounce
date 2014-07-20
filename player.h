#ifndef H_CLASS_PLAYER
#define H_CLASS_PLAYER

#include <SDL2/SDL.h>

#include "gameObject.h"
#include "eventListener.h"
#include "sprite.h"
#include "camera.h"

class Player: public GameObject, public Sprite {
protected:
	b2Vec2				lastCheckpoint;
	SDL_Texture*		explosion;
	SDL_Texture*		ball;
	Camera*				camera;
	int 				maxVelocity;
	
	int 				killedTime;
	int 				killedTimeNow;
	short int 			lives;
	bool 				onGround;
	// bool 			underWater;
	// bool				isBig;
	bool 				killed;
public:
	Player();
	Player(SDL_Renderer* renderer, Camera* camera);
	void 			setExplosionTexture(SDL_Texture* texture);
	void 			setPlayerTexture(SDL_Texture* texture);
	
	void 			control(EventListener* eventListener);
	void 			initBody(b2World* world, float x, float y);

	void			setCheckpoint(b2Vec2 position);

	void 			setOnGround(bool is);

	void 			addLifes(int i);
	int 			getLives();

	void 			birth(bool awake );

	bool 			getDeath();

	void 			kill();

	void 			draw();
};

#endif
 
