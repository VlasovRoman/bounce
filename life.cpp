#include "life.h"

Life::Life() : GameObject(LIF), iDrawable() {
	deleted = false;
}

void Life::initBody(b2World* world, float x, float y) {
	initStaticBodyDef();
	
	bodyDef.position = b2Vec2((x + 16) * 0.01f, (y + 16) * 0.01f);

	b2CircleShape shape;
	shape.m_radius = 16 * 0.01f;

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&shape, 1.0f);
}

void Life::draw(Painter* painter) {
	painter->drawLife(body->GetPosition().x * 100 - 16, body->GetPosition().y * 100 - 16);
}

void Life::setDelete() {
	deleted = true;
}

bool Life::isDeleted() {
	return deleted;
}