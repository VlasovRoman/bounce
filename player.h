#ifndef H_CLASS_PLAYER
#define H_CLASS_PLAYER

#include "gameObject.h"
#include "eventListener.h"
#include "iDrawable.h"
#include "camera.h"

class Player: public GameObject, public iDrawable  {
protected:
	Camera*				camera;

	b2Body*				bigBall;
	b2BodyDef			bigBallDef;
	b2FixtureDef		bigBallFixtureDef;

	b2FixtureDef 		fixture;

	b2Body*				lastBody;

	b2Vec2				lastCheckpoint;
	bool				lastType;

	float 				maxVelocity;
	float 				appliedVelocity;
	float 				jumpSpeed;
	
	bool				isBig;
	float 				radius;

	int 				bonusCount[3];

	int 				killedTimeNow;
	short int 			lives;
	
	bool 				onGround;
	bool				onJumpGround;
	bool 				underWater;

	void 	applyBonus(int bonusId);
	void 	deleteBonus(int bonusId);
	
	bool	isContactWithGround(b2Vec2 contactPoint);

	void 	destroyBody();
public:
	Player();
	Player(Painter* painter);
	~Player();

	void 			control(EventListener* eventListener);
	void 			initBody(b2World* world, float x, float y);

	void			setCheckpoint(b2Vec2 position);

	void			addBonus(int bonusId);

	void 			setUnderWater(bool is);

	void 			setCollisionPoint(b2Vec2 collisionPoint, bool jumpimngWall);

	void 			inflate();
	void			blowAway();

	void 			addLifes(int i);
	int 			getLives();

	void 			birth(bool awake, bool newLevel = false, int modificationId = false);

	bool 			getDeath();
	bool			getBig();

	void 			kill();

	b2Body* 		getBody();

	void 			draw(Painter* painter);
};

#endif
