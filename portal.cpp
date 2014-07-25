#include "portal.h"

Portal::Portal() : GameObject(END_LEVEL), iDrawable() {
	active = false;
}

void Portal::initBody(b2World* world, float x, float y) {
	initStaticBodyDef();
	b2Vec2 pos =  b2Vec2((x + 32) * 0.01f, (y + 32) * 0.01f);

	bodyDef.position = pos;

	b2PolygonShape shape;
	
	shape.SetAsBox(32 * 0.01f, 32 * 0.01f);

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&shape, 1.0f);
}

void Portal::setActive() {
	active = true;
}

bool Portal::getState() {
	return active;
}

void Portal::draw(Painter* painter) {
	float x = body->GetPosition().x * 100;
	float y = body->GetPosition().y * 100;

	painter->drawPortal(x - 32, y - 32, active);
}