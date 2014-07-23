#include "wall.h"
#include <iostream>

Wall::Wall() : GameObject(BLOCK) {}

Wall::Wall(BLOCK_TYPE type, bool jumpWall) : GameObject(BLOCK) {
	this->type = type;
	this->jumpWall = jumpWall;
}

void Wall::initBody(b2World* world, float x, float y) {
	initStaticBodyDef();
	// bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2((x + 16) * 0.01f, (y + 16) * 0.01f);
	// bodyDef.fixedRotation = true;
	// bodyDef.userData = this;
	
	body = world->CreateBody(&bodyDef);

	b2PolygonShape shape;

	if(type == SOLID) {
		shape.SetAsBox(16 * 0.01f, 16 * 0.01);
	}
	else if(type == DOWN_LEFT_EDGE) {
		b2Vec2 vertex[3];

		vertex[0] = b2Vec2((-16) * 0.01f, 16 * 0.01f);
		vertex[1] = b2Vec2((+16) * 0.01f, (-16) * 0.01f);
		vertex[2] = b2Vec2(16 * 0.01f, 16 * 0.01f);

		shape.Set(vertex, 3);
	}
	else if(type == DOWN_RIGHT_EDGE) {
		b2Vec2 vertex[3];

		vertex[0] = b2Vec2((-16) * 0.01f, 16 * 0.01f);
		vertex[1] = b2Vec2((-16) * 0.01f, (-16) * 0.01f);
		vertex[2] = b2Vec2(16 * 0.01f, 16 * 0.01f);

		shape.Set(vertex, 3);
	}
	else if(type == UP_LEFT_EDGE) {
		b2Vec2 vertex[3];

		vertex[0] = b2Vec2((-16) * 0.01f, (-16) * 0.01f);
		vertex[1] = b2Vec2((+16) * 0.01f, (-16) * 0.01f);
		vertex[2] = b2Vec2(16 * 0.01f, 16 * 0.01f);

		shape.Set(vertex, 3);
	}
	else if(type == UP_RIGHT_EDGE) {
		b2Vec2 vertex[3];

		vertex[0] = b2Vec2((-16) * 0.01f, (-16) * 0.01f);
		vertex[1] = b2Vec2((-16) * 0.01f, (+16) * 0.01f);
		vertex[2] = b2Vec2((+16) * 0.01f, (-16) * 0.01f);

		shape.Set(vertex, 3);
	}

	b2FixtureDef fixture;

	fixture.shape = &shape;
	fixture.friction = 1.0f;
	fixture.density = 1.0f;

	// if(jumpWall)
	// 	fixture.restitution = 1.5;
	// else
		fixture.restitution = 0;
	
	body->CreateFixture(&fixture);
}

bool Wall::isJumpWall() {
	return jumpWall;
}