#include "life.h"
#include <iostream>

Life::Life(SDL_Renderer* renderer, Camera* camera) : GameObject(LIF), Sprite(renderer) {
	this->camera = camera;
	deleted = false;
}

void Life::initBody(b2World* world, float x, float y) {
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(x * 0.01f, y * 0.01f);
	bodyDef.fixedRotation = true;
	bodyDef.userData = this;


	b2CircleShape shape;
	shape.m_radius = 16 * 0.01f;

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&shape, 1.0f);
}

void Life::draw() {
	Sprite::drawTexture(body->GetPosition().x * 100 - camera->x, body->GetPosition().y * 100 - camera->y);
}

void Life::setDelete() {
	deleted = true;
}

bool Life::isDeleted() {
	return deleted;
}