#include "portal.h"
#include "gameObject.h"

Portal::Portal(SDL_Renderer* renderer, Camera* camera) : GameObject(END_LEVEL), Sprite(renderer) {
	this->camera = camera;
	active = false;
}

void Portal::initBody(b2World* world, float x, float y) {
	bodyDef.type = b2_staticBody;
	bodyDef.position = b2Vec2(x * 0.01f, y * 0.01f);
	std::cout << x << " " << y << std::endl;
	bodyDef.fixedRotation = true;
	bodyDef.userData = this;

	b2PolygonShape shape;

	b2Vec2 vertex[4];
	vertex[0] = b2Vec2(-16 * 0.01f, -16 * 0.01f);
	vertex[1] = b2Vec2((64 - 16) * 0.01f, -16 * 0.01f);
	vertex[2] = b2Vec2((64 - 16) * 0.01f, (64 - 16) * 0.01f);
	vertex[3] = b2Vec2(-16 * 0.01f, (64 - 16) * 0.01f);
	
	shape.Set(vertex, 4);

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&shape, 1.0f);
	active = false;
}

void Portal::setActive() {
	active = true;
}

bool Portal::getState() {
	return active;
}

void Portal::setActiveTexture(SDL_Texture* texture) {
	activeTexture = texture;
}

void Portal::setLockedTexture(SDL_Texture* texture) {
	lockedTexture = texture;
}

void Portal::draw() {
	if(active) {
		Sprite::setTexture(activeTexture);
		Sprite::drawTexture(body->GetPosition().x * 100 - camera->x, body->GetPosition().y * 100 - camera->y);
	}
	else {
		Sprite::setTexture(lockedTexture);
		Sprite::drawTexture(body->GetPosition().x * 100 - camera->x, body->GetPosition().y * 100 - camera->y);
	}
}