#include "spike.h"

Spike::Spike() : GameObject(PIN) {

}

void Spike::setDirection(int directionId) {
	this->directionId = directionId;
}

void Spike::initBody(b2World* world, float x, float y) {
	initStaticBodyDef();

	bodyDef.position = b2Vec2((x + 16) * 0.01f, (y + 16) * 0.01f);
	
	b2PolygonShape shape;

	b2Vec2 vertex[3];

	if(directionId == 0)
		directionId = 17;
	if(directionId == 17) { //TM_UP
		vertex[0] = b2Vec2((-7) * 0.01f, 16 * 0.01f);
		vertex[1] = b2Vec2(0 * 0.01f, (-14) * 0.01f);
		vertex[2] = b2Vec2(7 * 0.01f, 16 * 0.01f);
	}
	if(directionId == 18) { //TM_RIGHT
		vertex[0] = b2Vec2((-16) * 0.01f, (-7) * 0.01f);
		vertex[1] = b2Vec2(14 * 0.01f, 0 * 0.01f);
		vertex[2] = b2Vec2((-16) * 0.01f, (+7) * 0.01f);
	}
	if(directionId == 27) { //TM_DOWN
		vertex[0] = b2Vec2((-7) * 0.01f, (-16) * 0.01f);
		vertex[1] = b2Vec2(0 * 0.01f, (+14) * 0.01f);
		vertex[2] = b2Vec2(7 * 0.01f, (-16) * 0.01f);
	}
	if(directionId == 28) { //TM_LEFT
		vertex[0] = b2Vec2((+16) * 0.01f, (-7) * 0.01f);
		vertex[1] = b2Vec2((-14) * 0.01f, 0 * 0.01f);
		vertex[2] = b2Vec2((+16) * 0.01f, (+7) * 0.01f);
	}

	shape.Set(vertex, 3);

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&shape, 1.0f);
}