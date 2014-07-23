#include "checkpoint.h"
#include <iostream>

Checkpoint::Checkpoint() : GameObject(CHECK), iDrawable() {
	active = false;
}

void Checkpoint::initBody(b2World* world, float x, float y) {
	initStaticBodyDef();
	bodyDef.position = b2Vec2((x + 16) * 0.01f, (y + 16) * 0.01f);

	b2PolygonShape shape;

	b2Vec2 vertex[4];
	vertex[0] = b2Vec2(0, -16 * 0.01f);
	vertex[1] = b2Vec2(16 * 0.01f, 0);
	vertex[2] = b2Vec2(0, 16 * 0.01f);
	vertex[3] = b2Vec2(-16 * 0.01f, 0);
	
	shape.Set(vertex, 4);

	body = world->CreateBody(&bodyDef);

	body->CreateFixture(&shape, 1.0f);
}

bool Checkpoint::getActive() {
	return active;
}

void Checkpoint::setActive(bool active) {
	this->active = active;
}

void Checkpoint::draw(Painter* painter) {
	float x = body->GetPosition().x * 100;
	float y = body->GetPosition().y * 100;

	painter->drawCheckpoint(x - 16, y - 16, active);
}