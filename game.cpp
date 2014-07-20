#include "game.h"

#include <Box2D/Box2D.h>
#include <SDL2/SDL.h>
#include "player.h"
#include "wall.h"
// #include "levels.h"
#include "ResInit.h"
#include "eventListener.h"
#include <iostream>
#include "spike.h"
#include "level.h"
#include "camera.h"
#include "checkpoint.h"

using namespace std;

Game::Game(SDL_Renderer* renderer)
{
	gravity = b2Vec2(0.0f, 6.0f);
	world = new b2World(gravity);


	timeStep = 1.0f / 60.0f;
	velocityIterations = 6;
	positionIterations = 2;
	cout << "Simulation parametres is seted" << endl;
	camera = new Camera;
	
	cout << "World created " << endl;
	player = new Player(renderer, camera);
	
	eventListener = NULL;
	contactListener = new ContactListener;
	world->SetContactListener(contactListener);
	contactListener->setPlayer(player);
	cout << "Listeners initialized" << endl;

	camera->x = 0;
	camera->y = 0;
	camera->width = 320;
	camera->height = 32 * 8;
	this->renderer = renderer;
	cout << "Set renderer and camera" << endl;

	level = Level(renderer, camera);
	cout << "Level initialized" << endl;

	cout << "Player created" << endl;
	player->setExplosionTexture(fail_tex);
	player->setPlayerTexture(ball_tex);
	cout << "Player textures init" << endl;

	portal = new Portal(renderer, camera);
	portal->setActiveTexture(loadTexture("resources/portalActive.png", renderer));
	portal->setLockedTexture(loadTexture("resources/portalLocked.png", renderer));

	levelId = 1;

	bLoadLevel = false;

	gui = new Gui(renderer);
	gui->initSprites();
}

void Game::createWorld() {

}

void Game::setEventListener(EventListener* listener) {
	eventListener = listener;
}

void Game::renderGui() {
	
}

void Game::frame() {
	if(contactListener->isNewLevel()) {
		levelId++;
		loadLevel();
	}
	if(player->getDeath()) {
		levelId = 1;
		loadLevel();
	}

	ringsNumber = 0;

	for(int i = 0; i < rings.size(); i++) {
		if(rings[i]->isActive()) {
			ringsNumber++;
		}
	}

	for(int i = 0; i < lifes.size(); i++) {
		if(lifes[i]->isDeleted()) {
			world->DestroyBody(lifes[i]->getBody());
			lifes.erase(lifes.begin() + i);
		}
	}

	player->control(eventListener);

	b2Vec2 playerPos = player->getBody()->GetPosition();
	playerPos.x *= 100;
	playerPos.y *= 100;

	if(playerPos.x > camera->width / 2) {
		camera->x = playerPos.x - camera->width / 2 + 16;
	}

	if(ringsNumber == 0)
		portal->setActive();

	world->Step(timeStep, velocityIterations, positionIterations);
}

void Game::render()	{
	level.draw();
	for(int i = 0; i < checkpoints.size(); i++) {
		checkpoints[i]->draw();
	}
	for(int i = 0; i < rings.size(); i++) {
		rings[i]->draw(RIGHT);
	}
	player->draw();
	for(int i = 0; i < rings.size(); i++) {
		rings[i]->draw(LEFT);
	}

	for(int i = 0; i < lifes.size(); i++) {
		lifes[i]->draw();
	}

	portal->draw();
	gui->draw(player, ringsNumber);
}

void Game::loadLevel()
{
	level = Level(renderer, camera);

	if(!level.loadFromFile("resources/level1.tmx")) {
		cout << "level not loaded" << endl;
	}

	map = level.getMap();

    walls.clear();
    spikes.clear();
    checkpoints.clear();
    rings.clear();

    delete world;
    world = new b2World(gravity);
    world->SetContactListener(contactListener);


	for(int y = 0; y < level.getMapSize().y; y++)
	{
		for(int x = 0; x < level.getMapSize().x; x++)
		{
			switch(map[x][y])
			{
			case 1:
				{
				    Wall* wall = new Wall();
				    wall->initBody(world, x * 32, y * 32);
				    walls.push_back(wall);
				} break;
			case 2:
				{
					player->initBody(world, x * 32 + 32, y * 32);
					player->birth(true);
				} break;
			case 3: 
				{
					portal->initBody(world, x * 32, y * 32);
				} break;
			case 4:
				{
				    Spike* spike = new Spike();
				    spike->initBody(world, x * 32, y * 32);
				    spikes.push_back(spike);
				} break;
			case 5: 
				{
					Checkpoint* chk = new Checkpoint(renderer, camera);
					chk->setOnTexture(onCheckpoint_tex);
					chk->setOffTexture(offCheckpoint_tex);
				    chk->initBody(world, x * 32, y * 32);
				    checkpoints.push_back(chk);	
				} break;
			case 6: 
				{
					Ring* ring = new Ring(renderer, camera);
					ring->init(VERTICALE, SMALL);
					ring->setOnTexture(onRingRight_tex, onRingLeft_tex);
					ring->setOffTexture(offRingRight_tex, offRingLeft_tex);
				    ring->initBody(world, x * 32, y * 32);
				    rings.push_back(ring);	
				} break;
			case 7: 
				{
					Ring* ring = new Ring(renderer, camera);
					ring->init(HORIZONTALE, SMALL);
					ring->setOnTexture(onRingRightHor_tex, onRingLeftHor_tex);
					ring->setOffTexture(offRingRightHor_tex, offRingLeftHor_tex);
				    ring->initBody(world, x * 32, y * 32);
				    rings.push_back(ring);	
				} break;
			case 8: 
				{
					Life* life = new Life(renderer, camera);
					life->setTexture(life_tex);
				    life->initBody(world, x * 32, y * 32);
				    lifes.push_back(life);
				} break;
			}
		}
	}

	ringsNumber = rings.size();

	cout << "Game objects created" << endl;
	bLoadLevel = false;
}