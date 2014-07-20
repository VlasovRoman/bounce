#include "spike.h"

Spike::Spike() : GameObject(PIN) {

}

void Spike::initBody(b2World* world, float x, float y) {
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(x * 0.01f, y * 0.01f);
	bodyDef.fixedRotation = true;
	bodyDef.userData = this;

	b2PolygonShape shape;

	b2Vec2 vertex[3];
	vertex[0] = b2Vec2((-7) * 0.01f, 16 * 0.01f);
	vertex[1] = b2Vec2(0 * 0.01f, (-14) * 0.01f);
	vertex[2] = b2Vec2(7 * 0.01f, 16 * 0.01f);

	shape.Set(vertex, 3);

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&shape, 1.0f);
}