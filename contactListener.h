#ifndef CONTACT_LISTNER
#define CONTACT_LISTNER

#include <Box2D/Box2D.h>
#include "player.h"
#include "gameObject.h"

class ContactListener : public b2ContactListener {
	bool 	newLevel;
	int 	big;
	Player* player;

	bool 	isObjectsCollising(GameObject* objectOne, GameObject* objectTwo, OBJECT_TYPE typeOne, OBJECT_TYPE typeTwo);
	b2Vec2	getCollisionPoint(b2Contact* contact, b2Body* staticBody);
	bool	isPlayerOnGround(b2Vec2 contactPoint);
public:
	ContactListener();
	~ContactListener();

	void 	setPlayer(Player* player);
	bool 	isNewLevel();
	int 	getPlayerState();

	void 	readingToNewFrame();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* manifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif