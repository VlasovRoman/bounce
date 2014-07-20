#ifndef CONTACT_LISTNER
#define CONTACT_LISTNER

#include <Box2D/Box2D.h>
#include "player.h"

class ContactListener : public b2ContactListener {
	bool newLevel;
	Player* player;
public:
	ContactListener();

	void setPlayer(Player* player);
	bool isNewLevel();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* manifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif