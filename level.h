#ifndef LEVEL
#define LEVEL

#include <Box2D/Box2D.h>
#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include "camera.h"
#include "sprite.h"
#include "tile.h"

using namespace std;

class Level {
	Painter* 			painter;
	
	Tile** 				map;
	int 				width, height;
	int 				tileWidth, tileHeight;
public:
	Level();
	Level(Painter* painter);

	bool			loadFromFile(std::string name);
	void 			clear();

	Tile**			getMap();

	b2Vec2			getMapSize();

	void 			draw();
};

#endif