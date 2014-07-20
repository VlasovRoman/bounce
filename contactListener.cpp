#include "contactListener.h"
#include "gameObject.h"
#include <iostream>
#include "checkpoint.h"
#include "ring.h"
#include "portal.h"
#include "life.h"

using namespace std;

ContactListener::ContactListener() : b2ContactListener() {
	newLevel = false;
}

void ContactListener::setPlayer(Player* player) {
	this->player = player;
}

bool ContactListener::isNewLevel() {
	bool level = newLevel;
	newLevel = false;
	return level;
}

void ContactListener::BeginContact(b2Contact* contact) {
}

void ContactListener::EndContact(b2Contact* contact) {
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* manifold) {
	b2Body* oneBody = contact->GetFixtureA()->GetBody();
	b2Body* twoBody = contact->GetFixtureB()->GetBody();

	newLevel = false;

	if(contact->IsTouching()) {
		if(oneBody->GetUserData() != NULL && twoBody->GetUserData() != NULL) {

			GameObject* objectA = (GameObject*)oneBody->GetUserData();
			GameObject* objectB = (GameObject*)twoBody->GetUserData();

			if(objectA->getType() == BLOCK || objectB->getType() == BLOCK)  {
				b2Body* playerBody;
				b2Body* blockBody;

				if(objectA->getType() == BALL) {
					playerBody = oneBody;
				blockBody = twoBody;
				}
				else {
					playerBody = twoBody;
					blockBody = oneBody;
				}

				b2Manifold* manifold = contact->GetManifold();
				b2Vec2	contactPoint = manifold->points[0].localPoint;
				b2Vec2	worldPoint = blockBody->GetWorldPoint(contactPoint);

				if(worldPoint.y * 100 > playerBody->GetPosition().y * 100) {
					player->setOnGround(true);
				}
			}

			if(objectA->getType() == END_LEVEL || objectB->getType() == END_LEVEL)  {
				Portal* portal;
				GameObject* object;
				if(objectA->getType() == END_LEVEL) {
					object = objectA;

					portal = dynamic_cast<Portal*>(object);
				}
				else {
					object = objectB;
					
					portal = dynamic_cast<Portal*>(object);
				}

				if(portal->getState()) {
					newLevel = true;
				}
				else
				{}
			}

			if(objectA->getType() == PIN || objectB->getType() == PIN)  {
				contact->SetEnabled(false);

				player->kill();
			}

			if(objectA->getType() == CHECK || objectB->getType() == CHECK) {
				contact->SetEnabled(false);

				player->setCheckpoint(oneBody->GetPosition());

				GameObject* object;
				if(objectA->getType() == CHECK) {
					object = objectA;
				}
				else
					object = objectB;

				Checkpoint* chk = dynamic_cast<Checkpoint*>(object);
				chk->setActive(true);
			}

			if(objectA->getType() == GOAL || objectB->getType() == GOAL)  {
				Ring* ring;
				contact->SetEnabled(false);
				
				float x1, y1;
				float x2, y2;

				x1 = oneBody->GetPosition().x * 100;
				y1 = oneBody->GetPosition().y * 100;

				x2 = twoBody->GetPosition().x * 100;
				y2 = twoBody->GetPosition().y * 100;

				GameObject* object;
				if(objectA->getType() == GOAL) {
					object = objectA;

					ring = dynamic_cast<Ring*>(object);
				}
				else {
					object = objectB;
					ring = dynamic_cast<Ring*>(object);
				}

				// if(ring->getOrientation() == HORIZONTALE) {
				// 	contact->SetEnabled(true);
				// }

				if(ring->getOrientation() == VERTICALE) {
					// x1 += 16;
					// y1 += 32;
					if((x1 - x2) * (x1 - x2) < 2.0f){
						ring->diactivate();
					}
				}
				if(ring->getOrientation() == HORIZONTALE) {
					x1 += 32;
					y1 += 16;

					x2 += 16;
					y2 += 16;

					if((y1 - y2) * (y1 - y2) < 3.0f){
						if((x1 - x2) * (x1 - x2) < 16.0f * 16.0f){
							ring->diactivate();
						}
					}
				}

				// if(y1 == y2) {
				// 	Ring* ring = dynamic_cast<Ring*>(object);
				// 	ring->diactivate();
				// }
			}

			if(objectA->getType() == LIF || objectB->getType() == LIF)  {
				contact->SetEnabled(false);

				player->addLifes(1);

				Life* life;

				GameObject* object;
				if(objectA->getType() == LIF) {
					object = objectA;

					life = dynamic_cast<Life*>(object);
				}
				else {
					object = objectB;
					life = dynamic_cast<Life*>(object);
				}

				life->setDelete();

				// if(y1 == y2) {
				// 	Ring* ring = dynamic_cast<Ring*>(object);
				// 	ring->diactivate();
				// }
			}
		}
		else {}
	}
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {

}