#include "player.h"
#include <SDL2/SDL.h>

#include "sprite.h"

#include <iostream>

using namespace std;


Player::Player() : GameObject(BALL), Sprite() {}

Player::Player(Painter* painter) : GameObject(BALL), Sprite(painter) {
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
	// cout << "Death" << endl;
	if(lives == 0)
		return true;
	else 
		return false;
}

void Player::initBody(b2World* world, float x, float y) {
	// cout << "Player body initialized" << endl;
	setCheckpoint(b2Vec2((x + 16) * 0.01f, (y + 16) * 0.01f));
	// lastCheckpoint = b2Vec2((x + 16) * 0.01f, (y + 16) * 0.01f);
	//Small ball
	{
		bodyDef.position = lastCheckpoint;
		bodyDef.type = b2_dynamicBody;
		bodyDef.linearDamping = 1.0f;
		bodyDef.fixedRotation = false;
		bodyDef.allowSleep = false;
		bodyDef.userData = this;
	
	
		b2CircleShape shape;
		shape.m_radius = 16 * 0.01f;
	
		fixture.shape = &shape;
		fixture.friction = 1.0f;
		fixture.density = 1.0f;
		// fixture.restitution = 0.5;
	
		body = world->CreateBody(&bodyDef);
		body->CreateFixture(&fixture);
	}

	//Big Ball
	{
		bigBallDef.position = b2Vec2(-64 * 0.01f, -64 * 0.01f);

		bigBallDef.type = b2_dynamicBody;
		bigBallDef.linearDamping = 1.0f;
		bigBallDef.fixedRotation = false;
		bigBallDef.allowSleep = false;
		bigBallDef.userData = this;

		b2CircleShape shape;
		shape.m_radius = 24 * 0.01f;

		bigBallFixtureDef.shape = &shape;
		bigBallFixtureDef.friction = 1.0f;
		bigBallFixtureDef.density = 1.0f;
		// bigBallFixtureDef.restitution = 0.5;

		bigBall = world->CreateBody(&bigBallDef);
		bigBall->CreateFixture(&bigBallFixtureDef);
	}

	lastBody = body;
	// cout << x << " " << y << endl;
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

	cout << "collisionPoint " << (int)(collisionPoint.x * 100) << " " << (int)(collisionPoint.y * 100) << endl;
	cout << "position " << (int)(lastBody->GetPosition().x * 100 + rad) << " " << (int)(lastBody->GetPosition().y * 100 + rad) << endl;

	if(((int)(collisionPoint.y * 100) > (int)(lastBody->GetPosition().y * 100)) &&  bonusCount[1] == 0){
		onGround = true;
	}
	if(((int)(collisionPoint.y * 100) < (int)(lastBody->GetPosition().y * 100)) && bonusCount[1] != 0) {
		onGround = true;
	}

	cout << onGround << endl;
	
	// cout << "control" << endl;
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

		// if(onJumpGround) {
		// 	cout << "On jump ground" << endl;
		// 	cout << velocity.y << endl;
		// 	velocity.y = -(velocity.y);
		// 	cout << velocity.y << endl;
		// }
		// else	
		// {}

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
	// cout << "Player body destroed" << endl;
	b2World* world = body->GetWorld();

	world->DestroyBody(body);
	world->DestroyBody(bigBall);
}

void Player::setOnGround(bool is) {
	// cout << "onGround: " << onGround << endl;;
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
	// cout << "Player birthed" << endl;
	killedTimeNow = 0;
	killed = false;

	if(modificationId == 10) {
		isBig = true;
		cout << "IS BIG" << endl;
	}

	if(awake){
		lives = 3;
		// isBig = false;
	}
	else {
		isBig = lastType;

	}
	if(isBig){
		inflate();
	}
	else
		blowAway();

	// cout << "LAST" << lastCheckpoint.x << " " << lastCheckpoint.y << endl;

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
	// cout << "Player killed" << endl;
	if(!killed) {
		killed = true;
		lives--;
	}
}

void Player::setCheckpoint(b2Vec2 position) {
	// cout << "Player checkpoint seted" << endl;
	lastCheckpoint = position;
	lastType = isBig;
}

void Player::draw() {
	// cout << "Player drawed" << endl;
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

	// body->SetUserData(NULL);
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
	painter = NULL;
}