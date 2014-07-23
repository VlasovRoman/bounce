#include "player.h"

#include <iostream>

using namespace std;

Player::Player(Painter* painter) : GameObject(BALL), iDrawable() {
	camera = painter->getCamera();
	onGround = false;
	underWater = false;
	onJumpGround = false;

	bonusCount[0] = 0;
	bonusCount[1] = 0;
	bonusCount[2] = 0;

	killed = false;
	lives = 3;

	killedTime = 20;
	killedTimeNow = 0;
	isBig = false;
	lastType = false;
	maxVelocity = 2;
	cout << "Player initialized" << endl;
}

bool Player::getDeath() {
	if(lives == 0)
		return true;
	else 
		return false;
}

void Player::initBody(b2World* world, float x, float y) {
	setCheckpoint(b2Vec2((x + 16) * 0.01f, (y + 16) * 0.01f));

	{
		initDynamicBodyDef();

		bodyDef.linearDamping = 1.0f;
		bodyDef.position = lastCheckpoint;
		bodyDef.fixedRotation = false;
		
		b2CircleShape shape;
		shape.m_radius = 16 * 0.01f;
	
		fixture.shape = &shape;
		fixture.friction = 1.0f;
		fixture.density = 1.0f;

		body = world->CreateBody(&bodyDef);
		body->CreateFixture(&fixture);
	}

	//Big Ball
	{
		initDynamicBodyDef(&bigBallDef);
		bigBallDef.linearDamping = 1.0f;
		
		bigBallDef.position = b2Vec2(-64 * 0.01f, -64 * 0.01f);

		bigBallDef.fixedRotation = false;

		b2CircleShape shape;
		shape.m_radius = 24 * 0.01f;

		bigBallFixtureDef.shape = &shape;
		bigBallFixtureDef.friction = 1.0f;
		bigBallFixtureDef.density = 1.0f;

		bigBall = world->CreateBody(&bigBallDef);
		bigBall->CreateFixture(&bigBallFixtureDef);
	}

	lastBody = body;
}

void Player::control(EventListener* eventListener) {
	int rad = 16;
	if(isBig)
		rad = 24;

	float appliedVelocity = 0.6;
	if(bonusCount[0] > 0) {
		appliedVelocity = 1.2;
		bonusCount[0]--;
		maxVelocity = 4;
	}
	else
		maxVelocity = 2;

	float jumpSpeed = 2.5f;
	if(bonusCount[1] > 0) {
		lastBody->SetGravityScale(-1.0f);
		bonusCount[1]--;
		jumpSpeed *= -1.0f;
	}
	else {
		lastBody->SetGravityScale(1.0f);
	}

	if(bonusCount[2] > 0) {
		jumpSpeed *= 3;
		bonusCount[2]--;
	}

	if(onJumpGround) {
		jumpSpeed *= 2;
	}

	cout << "collisionPoint " << (int)(collisionPoint.x * 100) << " " << (int)(collisionPoint.y * 100) << endl;
	cout << "position " << (int)(lastBody->GetPosition().x * 100 + rad) << " " << (int)(lastBody->GetPosition().y * 100 + rad) << endl;

	if(((int)(collisionPoint.y * 100) > (int)(lastBody->GetPosition().y * 100)) &&  bonusCount[1] == 0){
		onGround = true;
	}
	if(((int)(collisionPoint.y * 100) < (int)(lastBody->GetPosition().y * 100)) && bonusCount[1] != 0) {
		onGround = true;
	}

	cout << onGround << endl;
	
	if(killed) {
		killedTimeNow++;
	}
	else {
		if(underWater) {
			cout << "UNDER" << endl;
			if(!isBig) {
				lastBody->ApplyForceToCenter(b2Vec2(0.0f, -0.25f), false);
			}
			else 
				lastBody->ApplyForceToCenter(b2Vec2(0.0f, -1.5f), false);
		}
		b2Vec2 velocity = lastBody->GetLinearVelocity();

		if(eventListener->isKeyDown(KEY_RIGHT) && velocity.x < maxVelocity) {
			velocity += b2Vec2(+appliedVelocity, 0);
		}
		if(eventListener->isKeyDown(KEY_LEFT) && velocity.x > -maxVelocity) {
			velocity += b2Vec2(-appliedVelocity, 0);
		}
		if(eventListener->isKeyDown(KEY_UP) && onGround){
			velocity += b2Vec2(0.0f, -jumpSpeed);
		}

		onGround = false;
		onJumpGround = false;
		lastBody->SetLinearVelocity(velocity);
	}

	if(killedTimeNow >= killedTime) {
		birth(false);
	}

	underWater = false;
	onGround = false;
	collisionPoint = b2Vec2(0, 0);
}

bool Player::getBig() {
	return isBig;
}

void Player::destroyBody() {
	b2World* world = body->GetWorld();

	world->DestroyBody(body);
	world->DestroyBody(bigBall);
}

void Player::setOnGround(bool is) {
	onGround = is;
}

void Player::setUnderWater(bool is) {
	underWater = is;
}

void Player::addBonus(int bonusId) {
	if(bonusCount[bonusId] == 0) {
		bonusCount[bonusId] = 60 * 5;
	}
}

void Player::birth(bool awake, int modificationId) {
	killedTimeNow = 0;
	killed = false;

	if(modificationId == 10) {
		isBig = true;
		cout << "IS BIG" << endl;
	}

	if(awake){
		lives = 3;
	}
	else {
		isBig = lastType;

	}
	if(isBig){
		inflate();
	}
	else
		blowAway();

	lastBody->SetTransform(lastCheckpoint, 0.0f);
	lastBody->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

	camera->x = lastBody->GetPosition().x;
}

void Player::setCollisionPoint(b2Vec2 collisionPoint, bool jumpingWall) {
	if((collisionPoint.y == lastBody->GetPosition().y)) {
			cout << "Skipine..." << endl;
	}
	else
		this->collisionPoint = collisionPoint;
	onJumpGround = jumpingWall;
}

void Player::kill() {
	if(!killed) {
		killed = true;
		lives--;
	}
}

void Player::setCheckpoint(b2Vec2 position) {
	lastCheckpoint = position;
	lastType = isBig;
}

void Player::draw(Painter* painter) {
	int rad;
	if(isBig)
		rad = 24;
	else
		rad = 16;

	float x = lastBody->GetPosition().x * 100;
	float y = lastBody->GetPosition().y * 100;

	painter->drawBall(x - rad, y - rad, isBig, killed);
}

void Player::addLifes(int i) {
	lives += i;
}

int Player::getLives() {
	return lives;
}

void Player::inflate() {
	if(!isBig) {
		bigBall->SetTransform(body->GetPosition(), 0.0f);
	}
	lastBody = bigBall;

	bigBall->SetGravityScale(1.0f);
	body->SetGravityScale(0.0f);
	body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

	body->SetTransform(b2Vec2(-100 * 0.01f, 0.0 * 0.01f), 0.0f);

	isBig = true;
}

void Player::setOnJumpGround(bool is){
	onJumpGround = is;
}

void Player::blowAway() {
	if(isBig) {
		body->SetTransform(bigBall->GetPosition(), 0.0f);
	}
	lastBody = body;
	body->SetGravityScale(1.0f);
	bigBall->SetGravityScale(0.0f);
	bigBall->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

	bigBall->SetTransform(b2Vec2(-100 * 0.01f, 0.0 * 0.01f), 0.0f);

	isBig = false;
}

b2Body* Player::getBody() {
	return lastBody;
}

Player::~Player() {
	cout << "deleting player..." << endl;
	camera = NULL;
}