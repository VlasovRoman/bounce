#include "spider.h"
#include <SDL2/SDL.h>

#include "sprite.h"

#include <iostream>

using namespace std;


Spider::Spider() : GameObject(PAUK), Sprite(NULL) {}

Spider::Spider(Painter* painter) : GameObject(PAUK), Sprite(painter) {
	velocity = 1.0f;
	direction.deltaX = 0;
	direction.deltaY = 0;
	isRightPart = NULL;
}

void Spider::setWhole(bool is, bool isRight) {
	isWhole = is;

	if(!isWhole) {
		isRightPart = new bool;
		*isRightPart = isRight;
	}
}

void Spider::initBody(b2World* world, float x, float y) {
	initDynamicBodyDef();
	
	// if(isWhole) {

		bodyDef.position = b2Vec2((x + 32) * 0.01f, (y + 32) * 0.01f);
		// bodyDef.type = b2_dynamicBody;
		// bodyDef.linearDamping = 0;
		// bodyDef.fixedRotation = true;
		// bodyDef.allowSleep = false;
		// bodyDef.userData = this;


		b2PolygonShape shape;
		
		shape.SetAsBox(32 * 0.01f, 32 * 0.01f);

		body = world->CreateBody(&bodyDef);
		body->CreateFixture(&shape, 1.0f);
		body->SetGravityScale(0.0f);
		//body->SetLinearVelocity(speed);
	// }
	// else {
	// 	bodyDef.position = b2Vec2((x + 16) * 0.01f, (y + 32) * 0.01f);
	// 	// bodyDef.type = b2_dynamicBody;
	// 	// bodyDef.linearDamping = 0;
	// 	// bodyDef.fixedRotation = true;
	// 	// bodyDef.allowSleep = false;
	// 	// bodyDef.userData = this;


	// 	b2PolygonShape shape;
		
	// 	shape.SetAsBox(16 * 0.01f, 32 * 0.01f);

	// 	body = world->CreateBody(&bodyDef);
	// 	body->CreateFixture(&shape, 1.0f);
	// 	body->SetGravityScale(0.0f);
	// 	//body->SetLinearVelocity(speed);
	// }
	
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

void Spider::reverse() {
	// if(!alreadyChecked)
	// 	body->SetLinearVelocity(-(body->GetLinearVelocity()));
	// alreadyChecked = true;
}

void Spider::frame() {
	body->SetLinearVelocity(b2Vec2(velocity * direction.deltaX, velocity * direction.deltaY));
	//alreadyChecked = false;
}

void Spider::draw() {
	int shift = 32;

	if(!isWhole)
		shift = 16;
	// Sprite::drawTexture(body->GetPosition().x * 100 - camera->x - 32, body->GetPosition().y * 100 - camera->y - 32);
	painter->drawSpider(body->GetPosition().x * 100 - shift, body->GetPosition().y * 100 - shift, 0);
};