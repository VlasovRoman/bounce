#ifndef H_CLASS_GAME
#define H_CLASS_GAME

#include <Box2D/Box2D.h>
#include <vector>
#include <string>

#include "player.h"
#include "wall.h"
#include "eventListener.h"
#include "contactListener.h"
#include "portal.h"
#include "spike.h"
#include "level.h"
#include "checkpoint.h"
#include "ring.h"
#include "gui.h"
#include "tile.h"
#include "life.h"
#include "spider.h"
#include "arrow.h"
#include "pump.h"
#include "painter.h"
#include "water.h"
#include "bonus.h"

using namespace std;

class Game {
	//Physic world
	b2World*			world;
	b2Vec2				gravity;
	float32 			timeStep;
	int32				velocityIterations;
	int32 				positionIterations;
	//Listeners
	EventListener*		eventListener;
	ContactListener*	contactListener;

	//Renderers
	Painter*			painter;
	Camera*				camera;
	
	Level 				level;
	Tile**				map;

	vector<Wall*> 		walls; 
	vector<Spike*>		spikes; //ñïèñîê øèïîâ
	vector<Checkpoint*>	checkpoints;
	vector<Ring*>		rings;
	int 				ringsNumber;
	vector<Life*>		lifes;
	vector<Spider*> 	spiders;
	vector<Pump*>		pumps;
	vector<Water*>		waterBlocks;
	vector<Arrow*>		arrows;
	vector<Bonus*>		bonuses;
	
	Player*				player;
	Portal*				portal;

	Gui* 				gui;

	string 				levelsName[5];

	int 				levelId;

	void 				createWorld();
	void 				renderGui();
public:
	Game();
	Game(Painter* painter);

	~Game();
	
	void 			frame();
	void 			render();

	void 			setLevelId(int id);

	void 			setEventListener(EventListener* listener);

	void 			loadLevel();
};

#endif