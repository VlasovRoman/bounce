#include "life.h"

Life::Life(Painter* painter) : GameObject(LIF), Sprite(painter) {
	deleted = false;
}

void Life::initBody(b2World* world, float x, float y) {
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2((x + 16) * 0.01f, (y + 16) * 0.01f);
	bodyDef.fixedRotation = true;
	bodyDef.userData = this;


	b2CircleShape shape;
	shape.m_radius = 16 * 0.01f;

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&shape, 1.0f);
}

void Life::draw() {
	painter->drawLife(body->GetPosition().x * 100 - 16, body->GetPosition().y * 100 - 16);
}

void Life::setDelete() {
	deleted = true;
}

bool Life::isDeleted() {
	return deleted;
}