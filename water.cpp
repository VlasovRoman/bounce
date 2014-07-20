#include "water.h"
#include <iostream>

Water::Water() : GameObject(WTR) {}

void Water::initBody(b2World* world, float x, float y) {
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2((x + 16) * 0.01f, (y + 16) * 0.01f);
	bodyDef.fixedRotation = true;
	bodyDef.userData = this;
	
	body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;

	// if(type == SOLID) {
		shape.SetAsBox(16 * 0.01f, 16 * 0.01);
	// }
	// else if(type == DOWN_LEFT_EDGE) {
	// 	b2Vec2 vertex[3];

	// 	vertex[0] = b2Vec2((-16) * 0.01f, 16 * 0.01f);
	// 	vertex[1] = b2Vec2((+16) * 0.01f, (-16) * 0.01f);
	// 	vertex[2] = b2Vec2(16 * 0.01f, 16 * 0.01f);

	// 	shape.Set(vertex, 3);
	// }
	// else if(type == DOWN_RIGHT_EDGE) {
	// 	b2Vec2 vertex[3];

	// 	vertex[0] = b2Vec2((-16) * 0.01f, 16 * 0.01f);
	// 	vertex[1] = b2Vec2((-16) * 0.01f, (-16) * 0.01f);
	// 	vertex[2] = b2Vec2(16 * 0.01f, 16 * 0.01f);

	// 	shape.Set(vertex, 3);
	// }
	
	body->CreateFixture(&shape, 1.0f);
}