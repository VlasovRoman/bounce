#ifndef TILE
#define TILE

//numbers indicate on id of objects in tileset.png

enum TILE_ENVIRONMENT {
	TE_NONE = 0,
	TE_AIR = 1,
	TE_WATER = 33
};

enum TILE_OBJECT {
	TO_NONE = 0,
	TO_SPAWN = 3,
	TO_WALL_SOLID = 2,
	TO_WALL_DOWN_RIGHT_EDGE = 13,
	TO_WALL_DOWN_LEFT_EDGE = 12,
	TO_WALL_UP_RIGHT_EDGE = 23,
	TO_WALL_UP_LEFT_EDGE = 22, 
	TO_JUMP_WALL_DOWN_RIGHT_EDGE = 32,
	TO_JUMP_WALL_DOWN_LEFT_EDGE = 31,
	TO_JUMP_WALL_UP_RIGHT_EDGE = 42,
	TO_JUMP_WALL_UP_LEFT_EDGE = 41, 
	TO_JUMP_WALL = 21,
	TO_SPIKE = 9, 
	TO_PORTAL = 4,
	TO_RING_SMALL_VERT = 5,
	TO_RING_BIG_VERT = 6,
	TO_RING_SMALL_HOR = 7,
	TO_RING_BIG_HOR = 8,
	TO_LIFE = 11,
	TO_CHECKPOINT = 16,
	TO_SPIDER_1 = 19,
	TO_SPIDER_2 = 20,
	TO_SPIDER_3 = 29,
	TO_SPIDER_4 = 30,
	TO_PUMP_INFLATOR = 14,
	TO_PUMP_OUTPUT = 15,
	TO_BONUS_SPEED = 24, 
	TO_BONUS_WTF = 25,
	TO_BONUS_JUMP = 26
};

enum TILE_MODIFICATION {
	TM_NONE = 0,
	TM_BIG_BALL = 10,
	TM_UP = 17,
	TM_RIGHT = 18,
	TM_DOWN = 28,
	TM_LEFT = 27
};

struct Tile {
	TILE_ENVIRONMENT 	environment;
	TILE_OBJECT			object;
	TILE_MODIFICATION	modification;
};

#endif