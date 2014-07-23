#include "game.h"

#include <iostream>
#include "level.h"

using namespace std;

Game::Game(Painter* painter)
{
	camera = new Camera;
	camera->x = 0;
	camera->y = 0;
	camera->width = 320;
	camera->height = 32 * 8;

	this->painter = painter;
	painter->setCamera(camera);

	gravity = b2Vec2(0.0f, 6.0f);
	world = new b2World(gravity);

	timeStep = 1.0f / 60.0f;
	velocityIterations = 6;
	positionIterations = 2;

	// player->initBody(world, 0, 0);

	portal = NULL;

	// player = NULL;
	player = new Player(painter);
	// player->initBody(world, -100 * 32, -100 * 32);

	eventListener = NULL;

	contactListener = new ContactListener;
	contactListener->setPlayer(player);

	// world->SetContactListener(contactListener);

	level = Level(painter);

	gui = new Gui(painter);

	levelsName[0] = "resources/level1.tmx";
	levelsName[1] = "resources/level2.tmx";
	levelsName[2] = "resources/level3.tmx";
	levelsName[3] = "resources/level4.tmx";
	levelsName[4] = "resources/level5.tmx";
}

void Game::setLevelId(int id) {
	levelId = id + 1;
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

	// cout << contactListener->getPlayerState() << endl;

	if(contactListener->getPlayerState() > 0)
		player->inflate();
	if(contactListener->getPlayerState() < 0)  {
		// cout << "Blowing..." << endl;
		player->blowAway();
	}

	contactListener->readingToNewFrame();


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

	for(int i = 0; i < spiders.size(); i++) {
		spiders[i]->frame();
	}

	player->control(eventListener);

	b2Vec2 playerPos = player->getBody()->GetPosition();
	playerPos.x *= 100;
	playerPos.y *= 100;

	int cameraLevel = (int)playerPos.y / 32 / 7;

	camera->y = 7 * cameraLevel * 32;

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
		rings[i]->draw(true);
	}

	player->draw();

	for(int i = 0; i < rings.size(); i++) {
		rings[i]->draw(false);
	}

	for(int i = 0; i < lifes.size(); i++) {
		lifes[i]->draw();
	}

	for(int i = 0; i < spiders.size(); i++) {
		spiders[i]->draw();
	}

	portal->draw();
	gui->draw(player, ringsNumber);
}

void Game::loadLevel()
{
	string levelName = levelsName[levelId - 1];

	level.clear();

	if(!level.loadFromFile(levelName)) {
		cout << "level not loaded" << endl;
	}

	map = level.getMap();

    walls.clear();
    spikes.clear();
    checkpoints.clear();
    rings.clear();
    lifes.clear();
    spiders.clear();
    pumps.clear();
    waterBlocks.clear();
    bonuses.clear();

    int lives = 0;

	// if(player != NULL) {
 //    	lives = player->getLives();
 //    	if(lives == 0) {
 //    		lives -= 3;
 //    	}
	// 	player->destroyBody();
	// 	delete player;
	// // }
	// player = NULL;

	if(portal != NULL)
		delete portal;

    if(world != NULL) {
    	delete world;
    }

    world = new b2World(gravity);
    world->SetContactListener(contactListener);
    player->initBody(world, -10 * 32, -10 * 32);

	for(int y = 0; y < level.getMapSize().y; y++)
	{
		for(int x = 0; x < level.getMapSize().x; x++)
		{
			if(map[x][y].environment == TE_WATER) {
				Water* water = new Water();
				water->initBody(world, x * 32, y * 32);
				waterBlocks.push_back(water);
			}

			switch(map[x][y].object)
			{
			case TO_WALL_SOLID:
				{
				    Wall* wall = new Wall(SOLID);
				    wall->initBody(world, x * 32, y * 32);
				    walls.push_back(wall);
				} break;
			case TO_WALL_DOWN_LEFT_EDGE:
				{
				    Wall* wall = new Wall(DOWN_LEFT_EDGE);
				    wall->initBody(world, x * 32, y * 32);
				    walls.push_back(wall);
				} break;
			case TO_WALL_DOWN_RIGHT_EDGE:
				{
				    Wall* wall = new Wall(DOWN_RIGHT_EDGE);
				    wall->initBody(world, x * 32, y * 32);
				    walls.push_back(wall);
				} break;
			case TO_WALL_UP_RIGHT_EDGE:
				{
				    Wall* wall = new Wall(UP_RIGHT_EDGE);
				    wall->initBody(world, x * 32, y * 32);
				    walls.push_back(wall);
				} break;
			case TO_WALL_UP_LEFT_EDGE:
				{
				    Wall* wall = new Wall(UP_LEFT_EDGE);
				    wall->initBody(world, x * 32, y * 32);
				    walls.push_back(wall);
				} break;
			case TO_JUMP_WALL:
				{
					Wall* wall = new Wall(SOLID, true);
				    wall->initBody(world, x * 32, y * 32);
				    walls.push_back(wall);
				}break;
			case TO_JUMP_WALL_DOWN_LEFT_EDGE:
				{
				    Wall* wall = new Wall(DOWN_LEFT_EDGE, true);
				    wall->initBody(world, x * 32, y * 32);
				    walls.push_back(wall);
				} break;
			case TO_JUMP_WALL_DOWN_RIGHT_EDGE:
				{
				    Wall* wall = new Wall(DOWN_RIGHT_EDGE, true);
				    wall->initBody(world, x * 32, y * 32);
				    walls.push_back(wall);
				} break;
			case TO_JUMP_WALL_UP_RIGHT_EDGE:
				{
				    Wall* wall = new Wall(UP_RIGHT_EDGE, true);
				    wall->initBody(world, x * 32, y * 32);
				    walls.push_back(wall);
				} break;
			case TO_JUMP_WALL_UP_LEFT_EDGE:
				{
				    Wall* wall = new Wall(UP_LEFT_EDGE, true);
				    wall->initBody(world, x * 32, y * 32);
				    walls.push_back(wall);
				} break;
			case TO_SPAWN:
				{
					// player = new Player(painter);
					// player->initBody(world, x * 32, y * 32);
					player->setCheckpoint(b2Vec2(x * 32 * 0.01f, y * 32 * 0.01f));
					if(levelId == 1)
						player->birth(true, map[x][y].modification);
					else
						player->birth(false, map[x][y].modification);
				} break;
			case TO_PORTAL:
				{
					portal = new Portal(painter);
					portal->initBody(world, x * 32, y * 32);
				} break;
			case TO_SPIKE:
				{
				    Spike* spike = new Spike();
				    spike->setDirection(map[x][y].modification);
				    spike->initBody(world, x * 32, y * 32);
				    spikes.push_back(spike);
				    // map[x][y].modification = TM_NONE;
				} break;
			case TO_CHECKPOINT:
				{
					Checkpoint* chk = new Checkpoint(painter);
				    chk->initBody(world, x * 32, y * 32);
				    checkpoints.push_back(chk);
				} break;
			case TO_RING_SMALL_VERT:
				{
					Ring* ring = new Ring(painter);
					ring->init(true, false);
				    ring->initBody(world, x * 32, y * 32);
				    rings.push_back(ring);
				} break;
			case TO_RING_BIG_VERT:
				{
					Ring* ring = new Ring(painter);
					ring->init(true, true);
				    ring->initBody(world, x * 32, y * 32);
				    rings.push_back(ring);
				} break;
			case TO_RING_SMALL_HOR:
				{
					Ring* ring = new Ring(painter);
					ring->init(false, false);
				    ring->initBody(world, x * 32, y * 32);
				    rings.push_back(ring);
				} break;
			case TO_LIFE:
				{
					Life* life = new Life(painter);
				    life->initBody(world, x * 32, y * 32);
				    lifes.push_back(life);
				} break;

			case TO_SPIDER_1:
				{
					// if(map[x + 1][y].object == TO_SPIDER_2) {
						Spider* spider = new Spider(painter);
						spider->setWhole(true);
						spider->setDirection(map[x][y].modification);
						map[x][y].modification = TM_NONE;
						spider->setDirection(map[x + 1][y].modification);
						map[x + 1][y].modification = TM_NONE;
						spider->initBody(world, x * 32, y * 32);
						spiders.push_back(spider);
					// }
					// else {
					// 	Spider* spider = new Spider(painter);
					// 	spider->setWhole(false, false);
					// 	spider->initBody(world, x * 32, y * 32);
					// 	spiders.push_back(spider);
					// }
				} break;
			// case TO_SPIDER_2 : 
			// 	{
			// 		if(map[x - 1][y].object != TO_SPIDER_1) {
			// 			Spider* spider = new Spider(painter);
			// 			spider->setWhole(false, true);
			// 			spider->initBody(world, x * 32, y * 32);
			// 			spiders.push_back(spider);
			// 		}
			// 	} break;
			case TO_PUMP_INFLATOR:
				{
					Pump* pump = new Pump(INFLATOR);
				    pump->initBody(world, x * 32, y * 32);
				    pumps.push_back(pump);
				} break;
			case TO_PUMP_OUTPUT:
				{
					Pump* pump = new Pump(OUTPUT);
				    pump->initBody(world, x * 32, y * 32);
				    pumps.push_back(pump);
				} break;
			case TO_BONUS_SPEED:
				{
					Bonus* bonus = new Bonus(BT_SPEED);
					bonus->initBody(world, x * 32, y * 32);
					bonuses.push_back(bonus);
				} break;
			case TO_BONUS_WTF:
				{
					Bonus* bonus = new Bonus(BT_ANTIGRAVITATION);
					bonus->initBody(world, x * 32, y * 32);
					bonuses.push_back(bonus);
				} break;
			case TO_BONUS_JUMP:
				{
					Bonus* bonus = new Bonus(BT_JUMPING);
					bonus->initBody(world, x * 32, y * 32);
					bonuses.push_back(bonus);
				} break;
			}


			if(map[x][y].modification != TM_NONE) {
				if(map[x][y].object != TO_SPIKE || map[x][y].object != TO_PUMP_OUTPUT || map[x][y].object != TO_PUMP_INFLATOR) {

					switch(map[x][y].modification)
					{
					case TM_UP:
						{
						    Arrow* arrow = new Arrow(AT_UP);
						    arrow->initBody(world, x * 32, y * 32);
						    arrows.push_back(arrow);
						} break;
					case TM_RIGHT:
						{
						    Arrow* arrow = new Arrow(AT_RIGHT);
						    arrow->initBody(world, x * 32, y * 32);
						    arrows.push_back(arrow);
						} break;
					case TM_DOWN:
						{
						    Arrow* arrow = new Arrow(AT_DOWN);
						    arrow->initBody(world, x * 32, y * 32);
						    arrows.push_back(arrow);
						} break;
					case TM_LEFT:
						{
						    Arrow* arrow = new Arrow(AT_LEFT);
						    arrow->initBody(world, x * 32, y * 32);
						    arrows.push_back(arrow);
						} break;
					}
				}
			}
		}
	}

	// player->addLifes(lives);
	// player->inflate();

	contactListener->setPlayer(player);

	ringsNumber = rings.size();
}

Game::~Game() {
	// walls.clear();
 //    spikes.clear();
 //    checkpoints.clear();
 //    rings.clear();
 //    lifes.clear();
 //    // spiders.clear();
 //    // pumps.clear();

	// delete 	player;
	// delete 	portal;
	// delete 	contactListener;
	// eventListener = NULL;
	// painter = NULL;
	// camera = NULL;
	// delete 	gui;
	// delete 	world;

	cout << "Game cleared" << endl;
}
