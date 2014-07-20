#ifndef H_CLASS_PLAYER
#define H_CLASS_PLAYER

#include <SDL2/SDL.h>

#include "gameObject.h"
#include "eventListener.h"
#include "sprite.h"
#include "camera.h"

class Player: public GameObject, public Sprite {
protected:
	Camera*				camera;

	b2Body*				bigBall;
	b2BodyDef			bigBallDef;
	b2FixtureDef		bigBallFixtureDef;

	b2FixtureDef 		fixture;

	b2Body*				lastBody;

	b2Vec2				lastCheckpoint;
	bool				lastType;

	int 				maxVelocity;

	int 				bonusCount[3];

	int 				killedTime;
	int 				killedTimeNow;
	short int 			lives;
	bool 				onGround;
	bool				onJumpGround;
	bool 				underWater;
	bool				isBig;
	bool 				killed;
public:
	Player();
	Player(Painter* painter);
	~Player();

	void 			control(EventListener* eventListener);
	void 			initBody(b2World* world, float x, float y);
	void 			destroyBody();

	void			setCheckpoint(b2Vec2 position);

	void 			setOnGround(bool is);
	void 			setOnJumpGround(bool is);

	void			addBonus(int bonusId);

	void 			setUnderWater(bool is);

	void 			inflate();
	void			blowAway();

	void 			addLifes(int i);
	int 			getLives();

	void 			birth(bool awake );

	bool 			getDeath();
	bool			getBig();

	void 			kill();

	b2Body* 		getBody();

	void 			draw();
};

#endif
