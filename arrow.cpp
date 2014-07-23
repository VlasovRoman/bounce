#include "arrow.h"
#include <iostream>

Arrow::Arrow() : GameObject(DIRECTION) {}

Arrow::Arrow(ARROW_TYPE type) : GameObject(DIRECTION) {
	this->type = type;
	// this->jumpWall = jumpWall;
}

void Arrow::initBody(b2World* world, float x, float y) {
	initStaticBodyDef();
	// bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2((x + 16) * 0.01f, (y + 16) * 0.01f);
	// bodyDef.fixedRotation = true;
	// bodyDef.userData = this;
	
	body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;

	shape.SetAsBox(16 * 0.01f, 16 * 0.01);

	b2FixtureDef fixture;

	fixture.shape = &shape;
	fixture.friction = 1.0f;
	fixture.density = 1.0f;
	
	body->CreateFixture(&fixture);
}

ARROW_TYPE Arrow::getType() {
	return type;
}