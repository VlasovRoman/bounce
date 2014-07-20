#include "wall.h"
#include <iostream>

Wall::Wall() : GameObject(BLOCK) {}

void Wall::initBody(b2World* world, float x, float y) {
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(x * 0.01f, y * 0.01f);
	bodyDef.fixedRotation = true;
	bodyDef.userData = this;

	b2PolygonShape shape;

	shape.SetAsBox(16 * 0.01f, 16 * 0.01f);
	
	body = world->CreateBody(&bodyDef);

	body->CreateFixture(&shape, 1.0f);
}