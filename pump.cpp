#include "pump.h"
#include <iostream>

Pump::Pump() : GameObject(PUMPILA) {}

Pump::Pump(PUMP_TYPE pumpType) : GameObject(PUMPILA) {
	this->pumpType = pumpType;
}

void Pump::initBody(b2World* world, float x, float y) {
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2((x + 16) * 0.01f, (y + 16) * 0.01f);
	bodyDef.fixedRotation = true;
	bodyDef.userData = this;
	
	body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;

	shape.SetAsBox(16 * 0.01f, 16 * 0.01);
	
	body->CreateFixture(&shape, 1.0f);

}

PUMP_TYPE Pump::getPumpType() {
	return pumpType;
}