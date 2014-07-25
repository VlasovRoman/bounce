#include "spider.h"

Spider::Spider() : GameObject(PAUK), iDrawable() {
	direction.deltaX = 0;
	direction.deltaY = 0;
}

void Spider::initBody(b2World* world, float x, float y) {
	initDynamicBodyDef();

	bodyDef.position = b2Vec2((x + 32) * 0.01f, (y + 32) * 0.01f);

	b2PolygonShape shape;
	
	shape.SetAsBox(32 * 0.01f, 32 * 0.01f);

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&shape, 1.0f);
	body->SetGravityScale(0.0f);
}

void Spider::setDirection(int directionId) {
	if(directionId == 17) {
		direction.deltaY = -1;
	}
	if(directionId == 18) {
		direction.deltaX = 1;
	}
	if(directionId == 28) {
		direction.deltaY = 1;
	}
	if(directionId == 27) {
		direction.deltaX = 1;
	}
	else {}
}

void Spider::frame() {
	body->SetLinearVelocity(b2Vec2(1.0f * direction.deltaX, 1.0f * direction.deltaY));
}

void Spider::draw(Painter* painter) {
	painter->drawSpider(body->GetPosition().x * 100 - 32, body->GetPosition().y * 100 - 32);
};