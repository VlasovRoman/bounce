#include "ring.h"
#include <iostream>

Ring::Ring(SDL_Renderer* renderer, Camera* camera) : GameObject(GOAL), Sprite(renderer) {
	active = true;
	this->camera = camera;
}

void Ring::init(RING_ORIENTATION orientation, RING_TYPE type) {
	this->orientation = orientation;
	this->type = type;
}

void Ring::initBody(b2World* world, float x, float y) {
	if(orientation == VERTICALE) {
		bodyDef.type = b2_staticBody;
		bodyDef.position = b2Vec2(x * 0.01f, y * 0.01f);
		bodyDef.fixedRotation = true;
		bodyDef.userData = this;

		b2PolygonShape shape;
	
		shape.SetAsBox(16 * 0.01f, 32 * 0.01f);

		body = world->CreateBody(&bodyDef);

		body->CreateFixture(&shape, 1.0f);
	}
	if (orientation == HORIZONTALE)
	{
		bodyDef.type = b2_staticBody;
		bodyDef.position = b2Vec2(x * 0.01f, y * 0.01f);
		bodyDef.fixedRotation = true;
		bodyDef.userData = this;

		b2PolygonShape shape;
	
		shape.SetAsBox(32 * 0.01f, 16 * 0.01f);

		body = world->CreateBody(&bodyDef);

		body->CreateFixture(&shape, 1.0f);

		if(type == SMALL) {
			float boxSize = 0.3f;

			firstBodyDef.type = b2_staticBody;
			firstBodyDef.position = b2Vec2((x - 10) * 0.01f, (y + 2) * 0.01f);
			firstBodyDef.fixedRotation = true;
			firstBodyDef.userData = NULL;

			b2PolygonShape firstShape;
		
			firstShape.SetAsBox(boxSize * 0.01f, boxSize * 0.01f);

			firstBody = world->CreateBody(&firstBodyDef);

			firstBody->CreateFixture(&firstShape, 1.0f);



			secondBodyDef.type = b2_staticBody;
			secondBodyDef.position = b2Vec2((x + 64 - 18) * 0.01f, y * 0.01f);
			secondBodyDef.fixedRotation = true;
			secondBodyDef.userData = NULL;

			b2PolygonShape secondShape;
		
			secondShape.SetAsBox(boxSize * 0.01f, boxSize * 0.01f);

			secondBody = world->CreateBody(&secondBodyDef);

			secondBody->CreateFixture(&secondShape, 1.0f);
		}
		if (type == BIG) {
			//TODO
		}
	}



	// firstBodyDef.type = b2_staticBody;
	// firstBodyDef.position = b2Vec2(x * 0.01f, (y + 6) * 0.01f);
	// firstBodyDef.fixedRotation = true;
	// firstBodyDef.userData = NULL;

	// b2PolygonShape firstShape;
	
	// firstShape.SetAsBox(2 * 0.01f, 2 * 0.01f);

	// firstBody = world->CreateBody(&firstBodyDef);

	// firstBody->CreateFixture(&firstShape, 1.0f);
}

RING_ORIENTATION Ring::getOrientation() {
	return orientation;
}

void Ring::setOnTexture(SDL_Texture* right, SDL_Texture* left) {
	onTextureRight = right;
	onTextureLeft = left;
}

void Ring::setOffTexture(SDL_Texture* right, SDL_Texture* left) {
	offTextureRight = right;
	offTextureLeft = left;
}

void Ring::diactivate() {
	active = false;
}

bool Ring::isActive() {
	return active;
}

void Ring::draw(RING_PART part) {
	float x, y;
	x = body->GetPosition().x * 100;
	y = body->GetPosition().y * 100;

	if(part == RIGHT) {
		if(active) {
			Sprite::setTexture(onTextureRight);
			drawTexture(x - camera->x, y - camera->y);
		}
		else {
			Sprite::setTexture(offTextureRight);
			drawTexture(x - camera->x, y - camera->y);
		}
	}
	if(part == LEFT)  {
		if(active) {
			Sprite::setTexture(onTextureLeft);
			drawTexture(x - camera->x, y - camera->y);
		}
		else {
			Sprite::setTexture(offTextureLeft);
			drawTexture(x - camera->x, y - camera->y);
		}
	}
}