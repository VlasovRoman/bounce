#include "ring.h"

Ring::Ring() : GameObject(GOAL), iDrawable() {
	active = true;
	playerPosition = NULL;
	lastDelta = b2Vec2(0, 0);
}

void Ring::init(bool isVert, bool isBig) {
	this->isVert = isVert;
	this->isBig = isBig;
}

void Ring::initBody(b2World* world, float x, float y) {
	initStaticBodyDef();
	if(isVert) {
		bodyDef.position = b2Vec2((x + 16) * 0.01f, (y + 32) * 0.01f);

		b2PolygonShape shape;
		
		if(!isBig)
			shape.SetAsBox(10 * 0.01f, 20 * 0.01f);
		else
			shape.SetAsBox(16 * 0.01f, 32 * 0.01f);

		body = world->CreateBody(&bodyDef);

		body->CreateFixture(&shape, 1.0f);
	}
	else {
		bodyDef.position = b2Vec2((x + 32) * 0.01f, (y + 16) * 0.01f);
		b2PolygonShape shape;
	
		shape.SetAsBox(32 * 0.01f, 16 * 0.01f);

		body = world->CreateBody(&bodyDef);

		body->CreateFixture(&shape, 1.0f);
	}
}

bool Ring::getBig() {
	return isBig;
}

bool Ring::getOrientation() {
	return isVert;
}

void Ring::setPlayerPosition(b2Vec2* position) {
	playerPosition = position;
}

void Ring::checkOnThePassage() {
	if(active) {
		b2Vec2 delta;
		delta.x = playerPosition->x - body->GetPosition().x;
		delta.y = playerPosition->y - body->GetPosition().y;

		if(isVert) {

			if(delta.x > 0) {
				if(lastDelta.x < 0) {
					diactivate();
				}
				else {}
			}
			else {
				if(delta.x < 0) {
					if(lastDelta.x > 0) {
						diactivate();
					}
					else {}
				}
			}
		}
		else {
			if(delta.y > 0) {
				if(lastDelta.y < 0) {
					diactivate();
				}
				else {}
			}
			else {
				if(delta.y < 0) {
					if(lastDelta.y > 0) {
						diactivate();
					}
					else {}
				}
			}
		}
		lastDelta = delta;
		playerPosition = NULL;
	}
}

void Ring::diactivate() {
	active = false;
}

bool Ring::isActive() {
	return active;
}

void Ring::draw(Painter* painter,bool drawRightPart) {
	float x, y;
	x = body->GetPosition().x * 100;
	y = body->GetPosition().y * 100;

	if(isVert) {
		x -= 16;
		y -= 32;
	}
	else {
		// x += 16;
		x -= 16;
		y -= 32;
		// x -= 16;
		// y -= 32;
	}
	painter->drawRing(x, y, isBig, drawRightPart, isVert ,active);
}

void Ring::draw(Painter* painter) {

}