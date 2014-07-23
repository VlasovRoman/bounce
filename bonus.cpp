#include "bonus.h"
#include <iostream>

Bonus::Bonus() : GameObject(BONUSE) {}

Bonus::Bonus(BONUS_TYPE type) : GameObject(BONUSE) {
	this->type = type;
}

void Bonus::initBody(b2World* world, float x, float y) {
	initStaticBodyDef();

	bodyDef.position = b2Vec2((x + 16) * 0.01f, (y + 16) * 0.01f);
	
	body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;

	shape.SetAsBox(16 * 0.01f, 16 * 0.01);

	b2FixtureDef fixture;

	fixture.shape = &shape;
	fixture.friction = 1.0f;
	fixture.density = 1.0f;

	body->CreateFixture(&fixture);
}

BONUS_TYPE	Bonus::getType() {
	return type;
}