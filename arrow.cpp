#include "arrow.h"

Arrow::Arrow() : GameObject(DIRECTION) {}

Arrow::Arrow(ARROW_TYPE type) : GameObject(DIRECTION) {
	this->type = type;
}

void Arrow::initBody(b2World* world, float x, float y) {
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

ARROW_TYPE Arrow::getType() {
	return type;
}