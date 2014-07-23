#ifndef LEVEL
#define LEVEL

#include <Box2D/Box2D.h>
#include <string>
#include "painter.h"
#include "tile.h"

class Level {	
	Tile** 				map;
	int 				width, height;
	int 				tileWidth, tileHeight;
public:
	Level();

	bool			loadFromFile(std::string name);
	void 			clear();

	Tile**			getMap();

	b2Vec2			getMapSize();

	void 			draw(Painter* painter);
};

#endif