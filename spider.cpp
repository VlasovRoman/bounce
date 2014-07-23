#include "spider.h"

Spider::Spider() : GameObject(PAUK), iDrawable() {
	velocity = 1.0f;
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

void Spider::setDirection(int x, int y) {
	if(x > 0) {
		direction.deltaX = y;
	}
	else
		direction.deltaY = y;
}

void Spider::setDirection(int directionId) {
	if(directionId == 17) {
		setDirection(-1, -1);
	}
	if(directionId == 18) {
		setDirection(1, 1);
	}
	if(directionId == 28) {
		setDirection(-1, 1);
	}
	if(directionId == 27) {
		setDirection(1, -1) ;
	}
	else {}
}

void Spider::frame() {
	body->SetLinearVelocity(b2Vec2(velocity * direction.deltaX, velocity * direction.deltaY));
}

void Spider::draw(Painter* painter) {
	painter->drawSpider(body->GetPosition().x * 100 - 32, body->GetPosition().y * 100 - 32, 0);
};