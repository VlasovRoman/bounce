#ifndef LEVEL
#define LEVEL

#include <Box2D/Box2D.h>
#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include "camera.h"
#include "sprite.h"

using namespace std;

class Level {
	int** 				map;
	SDL_Renderer*		renderer;
	Camera*				camera;
	int 				width, height;
	int 				tileWidth, tileHeight;
	Sprite				sprites[5]; //TODO
public:
	Level();
	Level(SDL_Renderer* renderer, Camera* camera);

	bool			loadFromFile(std::string name);
	void 			clear();

	int**			getMap();

	b2Vec2			getMapSize();

	void 			draw();
};

#endif