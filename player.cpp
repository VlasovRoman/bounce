#include "player.h"

Player::Player(Painter* painter) : GameObject(BALL), iDrawable() {
	camera = painter->getCamera();
	onGround = false;
	underWater = false;
	onJumpGround = false;

	bonusCount[0] = 0;
	bonusCount[1] = 0;
	bonusCount[2] = 0;

	killedTimeNow = 0;
	lives = 3;

	lastType = false;
	
	isBig = false;
	radius = 15.4;

	maxVelocity = 2;
	appliedVelocity =0.6f;
	jumpSpeed = 2.5f;
}

void Player::initBody(b2World* world, float x, float y) {
	setCheckpoint(b2Vec2((x + radius) * 0.01f, (y + radius) * 0.01f));

	{
		initDynamicBodyDef();

		bodyDef.linearDamping = 1.0f;
		bodyDef.position = lastCheckpoint;
		bodyDef.fixedRotation = false;
		
		b2CircleShape shape;
		shape.m_radius = radius * 0.01f;
	
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

void Player::birth(bool awake, bool newLevel, int modificationId) {
	killedTimeNow = 0;
	// killed = false;

	if(modificationId == 10) {
		isBig = true;
	}

	if(awake){
		lives = 3;
	}
	else {
		if(!newLevel)
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

void Player::kill() {
	if(!killedTimeNow ) {
		killedTimeNow = 20;
		lives--;
	}
}

void Player::control(EventListener* eventListener) {

	for(int i = 0; i < 3; i++)  {
		if(bonusCount[i] > 0) {
			bonusCount[i]--;

			if(bonusCount[i] == 0) {
				deleteBonus(i);
			}
		}
	}

	jumpSpeed = 2.5f;

	if(onJumpGround) {
		jumpSpeed *= 2;
	}
	
	if(killedTimeNow) {
		killedTimeNow--;

		if(!killedTimeNow) {
			birth(false);
		}
	}
	else{
		if(underWater) {
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

		lastBody->SetLinearVelocity(velocity);
	}

	underWater = false;
	onGround = false;
	onJumpGround = false;
}

void Player::setCheckpoint(b2Vec2 position) {
	lastCheckpoint = position;
	lastType = isBig;
}

void Player::addBonus(int bonusId) {
	if(bonusCount[bonusId] == 0) {
		bonusCount[bonusId] = 60 * 5;
		applyBonus(bonusId);
	}
}

void Player::setUnderWater(bool is) {
	underWater = is;
}

void Player::setCollisionPoint(b2Vec2 collisionPoint, bool jumpingWall) {
	if(collisionPoint.y != lastBody->GetPosition().y) {
		isContactWithGround(collisionPoint);
	}

	onJumpGround = jumpingWall;
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

	radius = 24;

	isBig = true;
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

	radius = 15.4f;

	isBig = false;
}

void Player::addLifes(int i) {
	lives += i;
}

int Player::getLives() {
	return lives;
}

bool Player::getDeath() {
	if(lives == 0 && killedTimeNow == 0)
		return true;
	else 
		return false;
}

bool Player::getBig() {
	return isBig;
}

b2Body* Player::getBody() {
	return lastBody;
}

void Player::draw(Painter* painter) {
	bool killed = killedTimeNow;

	float x = lastBody->GetPosition().x * 100;
	float y = lastBody->GetPosition().y * 100;

	painter->drawBall(x - radius, y - radius, isBig, killed);
}

bool Player::isContactWithGround(b2Vec2 collisionPoint) {
	if(((int)(collisionPoint.y * 100) > (int)(lastBody->GetPosition().y * 100)) &&  bonusCount[1] == 0){
		onGround = true;
	}
	if(((int)(collisionPoint.y * 100) < (int)(lastBody->GetPosition().y * 100)) && bonusCount[1] != 0) {
		onGround = true;
	}
}

void Player::applyBonus(int bonusId) {
	if(bonusId == 0) {
		maxVelocity *= 2;
		appliedVelocity *= 2;
	}
	else if(bonusId == 1) {
		lastBody->SetGravityScale(-1.0f);
		jumpSpeed *= -1.0f;
	}
	else if(bonusId == 2) {
		jumpSpeed *= 2.5;
	}
}

void Player::deleteBonus(int bonusId) {
	if(bonusId == 0) {
		maxVelocity /= 2;
		appliedVelocity /= 2;
	}
	else if(bonusId == 1) {
		lastBody->SetGravityScale(1.0f);
		jumpSpeed *= -1.0f;
	}
	else if(bonusId == 2) {
		jumpSpeed /= 2.5;
	}	
}

Player::~Player() {
	camera = NULL;
	body = NULL;
	bigBall = NULL;
	lastBody = NULL;
}