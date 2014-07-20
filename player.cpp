#include "player.h"
#include <SDL2/SDL.h>

#include "sprite.h"

#include <iostream>

using namespace std;


Player::Player() : GameObject(BALL), Sprite(NULL) {}

Player::Player(SDL_Renderer* renderer, Camera* camera) : GameObject(BALL), Sprite(renderer) {
	this->camera = camera;
	onGround = false;

	killed = false;
	lives = 3;

	killedTime = 20;
	killedTimeNow = 0;
	maxVelocity = 2;
}

void Player::setExplosionTexture(SDL_Texture* texture) {
	explosion = texture;
}

void Player::setPlayerTexture(SDL_Texture* texture) {
	ball = texture;
}

bool Player::getDeath() {
	if(lives == 0)
		return true;
	else 
		return false;
}

void Player::initBody(b2World* world, float x, float y) {
	lastCheckpoint = b2Vec2(x * 0.01f, y * 0.01f);

	bodyDef.position = lastCheckpoint;
	bodyDef.type = b2_dynamicBody;
	bodyDef.linearDamping = 1.0f;
	bodyDef.fixedRotation = false;
	bodyDef.allowSleep = false;
	bodyDef.userData = this;


	b2CircleShape shape;
	shape.m_radius = 16 * 0.01f;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.friction = 1.0f;
	fixture.density = 1.0f;
	fixture.filter.groupIndex = 1;

	body = world->CreateBody(&bodyDef);
	body->CreateFixture(&fixture);
}

void Player::control(EventListener* eventListener) {
	if(killed) {
		killedTimeNow++;
	}
	else {
		b2Vec2 velocity = body->GetLinearVelocity();

		if(eventListener->isKeyDown(KEY_RIGHT) && velocity.x < maxVelocity) {
			velocity += b2Vec2(+0.6f, 0);
		}
		if(eventListener->isKeyDown(KEY_LEFT) && velocity.x > -maxVelocity) {
			velocity += b2Vec2(-0.6f, 0);
		}
		if(eventListener->isKeyDown(KEY_UP) && onGround){	
			velocity += b2Vec2(0.0f, -2.5f);
		}
		body->SetLinearVelocity(velocity);
		onGround = false;
	}
	if(killedTimeNow >= killedTime) {
		birth(false);
	}
}

void Player::setOnGround(bool is) {
	onGround = is;
}

void Player::birth(bool awake) {
	Sprite::setTexture(ball);
	killedTimeNow = 0;
	killed = false;
	body->SetTransform(lastCheckpoint, 0.0f);

	if(awake)
		lives = 3;

	body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

	camera->x = body->GetPosition().x;
}

void Player::kill() {
	if(!killed) {
		killed = true;
		Sprite::setTexture(explosion);
		lives--;
	}
}

void Player::setCheckpoint(b2Vec2 position) {
	lastCheckpoint = position;
}

void Player::draw() {
	Sprite::drawTexture(body->GetPosition().x * 100 - camera->x, body->GetPosition().y * 100 - camera->y);
}

void Player::addLifes(int i) {
	lives += i;
}

int Player::getLives() {
	return lives;
}