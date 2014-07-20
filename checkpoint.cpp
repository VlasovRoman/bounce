#include "checkpoint.h"
#include <iostream>

Checkpoint::Checkpoint(SDL_Renderer* renderer, Camera* camera) : GameObject(CHECK), Sprite(renderer) {
	active = false;
	this->camera = camera;
}

void Checkpoint::initBody(b2World* world, float x, float y) {
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(x * 0.01f, y * 0.01f);
	bodyDef.fixedRotation = true;
	bodyDef.userData = this;

	b2PolygonShape shape;

	b2Vec2 vertex[4];
	vertex[0] = b2Vec2(0, -16 * 0.01f);
	vertex[1] = b2Vec2(16 * 0.01f, 0);
	vertex[2] = b2Vec2(0, 16 * 0.01f);
	vertex[3] = b2Vec2(-16 * 0.01f, 0);
	
	shape.Set(vertex, 4);

	body = world->CreateBody(&bodyDef);

	body->CreateFixture(&shape, 1.0f);
}

void Checkpoint::setOnTexture(SDL_Texture* texture) {
	onTexture = texture;
}

void Checkpoint::setOffTexture(SDL_Texture* texture) {
	offTexture = texture;
}

bool Checkpoint::getActive() {
	return active;
}

void Checkpoint::setActive(bool active) {
	this->active = active;
}

void Checkpoint::draw() {
	if(active) {
		Sprite::setTexture(onTexture);
		drawTexture(body->GetPosition().x * 100 - camera->x, body->GetPosition().y * 100 - camera->y);
	}
	else {
		Sprite::setTexture(offTexture);
		drawTexture(body->GetPosition().x * 100 - camera->x, body->GetPosition().y * 100 - camera->y);
	}
}