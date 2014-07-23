#include "contactListener.h"
#include "gameObject.h"
#include <iostream>
#include "checkpoint.h"
#include "ring.h"
#include "portal.h"
#include "life.h"
#include "spider.h"
#include "pump.h"
#include "wall.h"
#include "arrow.h"
#include "bonus.h"

using namespace std;

ContactListener::ContactListener() : b2ContactListener() {
	newLevel = false;
	big = 0;
}

void ContactListener::setPlayer(Player* player) {
	this->player = player;
}

bool ContactListener::isNewLevel() {
	return newLevel;
}

int ContactListener::getPlayerState() {
	return big;
}

void ContactListener::readingToNewFrame() {
	big = 0;
	newLevel = false;
}

bool ContactListener::isObjectsCollising(GameObject* objectOne, GameObject* objectTwo, OBJECT_TYPE typeOne, OBJECT_TYPE typeTwo) {
	if(objectOne->getType() == typeOne || objectTwo->getType() == typeOne)  {
		if(objectOne->getType() == typeTwo || objectTwo->getType() == typeTwo) {
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

b2Vec2 ContactListener::getCollisionPoint(b2Contact* contact, b2Body* staticBody) {
	b2Manifold* manifold = contact->GetManifold();
	b2Vec2	contactPoint = manifold->points[0].localPoint;
	b2Vec2	worldPoint = staticBody->GetWorldPoint(contactPoint);

	// if(worldPoint.y * 100 > playerBody->GetPosition().y * 100) {

	// 	Wall* wall;
	// 	GameObject* wallObject;
	// 	// cout << "Player on ground" << endl;
	// 	if(objectA->getType() == BLOCK) {
	// 		wallObject = objectA;
	// 		wall = dynamic_cast<Wall*>(wallObject);
	// 	}
	// 	else {
	// 		wallObject = objectB;
				
	// 		wall = dynamic_cast<Wall*>(wallObject);
	// 	}
	// 	if(wall->isJumpWall())
	// 		player->setOnJumpGround(true);

	// 	player->setOnGround(true);
	// }
}

bool ContactListener::isPlayerOnGround(b2Vec2 contactPoint) {
	b2Body* playerBody = player->getBody();
	if(contactPoint.y * 100 > playerBody->GetPosition().y * 100) {
		player->setOnGround(true);
	}
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

			if(isObjectsCollising(objectA, objectB, BLOCK, BALL) /* || isObjectsCollising(objectA, objectB, BALL, PUMPILA)*/) {
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
				b2WorldManifold worldManifold;
				contact->GetWorldManifold(&worldManifold);

				b2Vec2	contactPoint = worldManifold.points[0];
				b2Vec2	worldPoint = blockBody->GetWorldPoint(contactPoint);
				// cout << "contactPoint " << contactPoint.x * 100 << " " << contactPoint.y * 100 << endl;
				// cout << "worldPoint " << worldPoint.x * 100 << " " << worldPoint.y * 100 << endl;

				// if(worldPoint.y * 100 > playerBody->GetPosition().y * 100) {

					Wall* wall;
					GameObject* wallObject;
					// cout << "Player on ground" << endl;
					if(objectA->getType() == BLOCK) {
						wallObject = objectA;
						wall = dynamic_cast<Wall*>(wallObject);
					}
					else {
						wallObject = objectB;
							
						wall = dynamic_cast<Wall*>(wallObject);
					}

				// 	player->setOnGround(true);
				// }
				player->setCollisionPoint(contactPoint, wall->isJumpWall());
				// else
				// 	player->setOnGround(false);
			}

			if(isObjectsCollising(objectA, objectB, BALL, END_LEVEL)) {
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

			if(isObjectsCollising(objectA, objectB, BALL, PIN))  {
				contact->SetEnabled(false);

				player->kill();
			}

			if(isObjectsCollising(objectA, objectB, BALL, DIRECTION)) {
				contact->SetEnabled(false);
			}

			if(isObjectsCollising(objectA, objectB, BALL, BONUSE)) {
				Bonus* bonus;
				GameObject* object;

				if(objectA->getType() == BONUSE) {
					object = objectA;
					bonus = dynamic_cast<Bonus*>(object);
				}
				else {
					object = objectB;
						
					bonus = dynamic_cast<Bonus*>(object);
				}

				if(bonus->getType() == BT_SPEED) {
					player->addBonus(0);
				}
				else if(bonus->getType() == BT_ANTIGRAVITATION) {
					player->addBonus(1);
				}
				else {
					player->addBonus(2);
				}
			}

			if(isObjectsCollising(objectA, objectB, PAUK, DIRECTION)) {
				contact->SetEnabled(false);

				b2Body* spiderBody;
				b2Body* directionBody;

				Spider* spider;
				Arrow* arrow;

				GameObject* object;

				if(objectA->getType() == PAUK) {
					object = objectA;

					spiderBody = oneBody;
					directionBody = twoBody;

					spider = dynamic_cast<Spider*>(object);
					arrow = dynamic_cast<Arrow*>(objectB);
				}
				else {
					object = objectB;

					spiderBody = twoBody;
					directionBody = oneBody;
					
					spider = dynamic_cast<Spider*>(object);
					arrow = dynamic_cast<Arrow*>(objectA);
				}

				if(arrow->getType() == AT_UP) {
					spider->setDirection(-1, -1);
				}
				if(arrow->getType() == AT_RIGHT) {
					spider->setDirection(1, 1);
				}
				if(arrow->getType() == AT_DOWN) {
					spider->setDirection(-1, 1);
				}
				if(arrow->getType() == AT_LEFT) {
					spider->setDirection(1, -1);
				}

			}

			if(isObjectsCollising(objectA, objectB, PAUK, PAUK) || isObjectsCollising(objectA, objectB, PAUK, BLOCK))  {
				contact->SetEnabled(false);
			}

			if(isObjectsCollising(objectA, objectB, BALL, PAUK)) {
				contact->SetEnabled(false);

				player->kill();
			}

			if(isObjectsCollising(objectA, objectB, BALL, PUMPILA)) {

				Pump* pump;
				GameObject* object;

				if(objectA->getType() == PUMPILA) {
					object = objectA;

					pump = dynamic_cast<Pump*>(object);
				}
				else {
					object = objectB;
					
					pump = dynamic_cast<Pump*>(object);
				}

				b2Vec2 contactPoint = getCollisionPoint(contact, object->getBody());
				if(isPlayerOnGround(contactPoint)) {
					player->setOnGround(true);
				}

				if(pump->getPumpType() == INFLATOR){
					big = 1;
				}
				else {
					big = -1;
				}
			}


			if(isObjectsCollising(objectA, objectB, BALL, CHECK)) {
				contact->SetEnabled(false);


				GameObject* object;
				if(objectA->getType() == CHECK) {
					object = objectA;
				}
				else
					object = objectB;

				Checkpoint* chk = dynamic_cast<Checkpoint*>(object);

				if(!chk->getActive())
					player->setCheckpoint(oneBody->GetPosition());

				chk->setActive(true);
			}

			if(isObjectsCollising(objectA, objectB, BALL, GOAL))  {
				//TODO
				//Event work anly when coords changed
				Ring* ring;
				GameObject* object;
				if(objectA->getType() == GOAL) {
					object = objectA;

					ring = dynamic_cast<Ring*>(object);
				}
				else {
					object = objectB;
					ring = dynamic_cast<Ring*>(object);
				}

				if(!player->getBig())
					contact->SetEnabled(false);
				else {
					if(ring->getBig())
						contact->SetEnabled(false);
					else
					{}
				}
				

				ring->setPlayerPosition((b2Vec2*)&player->getBody()->GetPosition());
				ring->checkOnThePassage();
				// ring->iterate();
				// float x1, y1;
				// float x2, y2;

				// x1 = oneBody->GetPosition().x * 100;
				// y1 = oneBody->GetPosition().y * 100;

				// x2 = twoBody->GetPosition().x * 100;
				// y2 = twoBody->GetPosition().y * 100;


				// if(ring->getOrientation() == HORIZONTALE) {
				// 	contact->SetEnabled(true);
				// }

				// if(ring->getOrientation()) {
				// 	// x1 += 16;
				// 	// y1 += 32;
				// 	// if((x1 - x2) * (x1 - x2) < 2.0f){
				// 	// 	ring->diactivate();
				// 	// }
				// }
				// else {
				// 	// x1 += 32;
				// 	// y1 += 16;

				// 	// x2 += 16;
				// 	// y2 += 16;

				// 	// if((y1 - y2) * (y1 - y2) < 3.0f){
				// 	// 	if((x1 - x2) * (x1 - x2) < 16.0f * 16.0f){
				// 	// 		ring->diactivate();
				// 	// 	}
				// 	// }
				// }

				// if(y1 == y2) {
				// 	Ring* ring = dynamic_cast<Ring*>(object);
				// 	ring->diactivate();
				// }

			}

			if(isObjectsCollising(objectA, objectB, BALL, LIF))  {
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
			}

			if(isObjectsCollising(objectA, objectB, BALL, WTR))  {
				contact->SetEnabled(false);

				player->setUnderWater(true);
				// b2Body* playerBody = player->getBody();

				// playerBody->ApplyForceToCenter(b2Vec2(0.0f, -0.1f), false);
			}
		}
	}
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {

}
ContactListener::~ContactListener() {
	player = NULL;
}