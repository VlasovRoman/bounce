#ifndef H_CLASS_GAME
#define H_CLASS_GAME

#include <SDL2/SDL.h>
#include <Box2D/Box2D.h>
#include <vector>

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
#include "life.h"

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
	SDL_Renderer* 		renderer;
	Camera*				camera;
	
	Level 				level;
	int**				map;

	vector<Wall*> 		walls; 
	vector<Spike*>		spikes; //ñïèñîê øèïîâ
	vector<Checkpoint*>	checkpoints;
	vector<Ring*>		rings;
	int 				ringsNumber;
	vector<Life*>		lifes;
	
	Player*				player;
	Portal*				portal;

	Gui* 				gui;


	int 				levelId;
	bool 				bLoadLevel;

	void 				createWorld();
	void 				renderGui();
public:
	Game(){};
	Game(SDL_Renderer* renderer);
	
	void 			frame();
	void 			render();

	void 			setEventListener(EventListener* listener);

	void 			loadLevel();
};

#endif