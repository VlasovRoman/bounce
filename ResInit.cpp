#include "ResInit.h"
#include <iostream>

SDL_Texture*			gameover_tex = NULL;
SDL_Texture*			wall_tex = NULL;
SDL_Texture*			space_tex = NULL;
SDL_Texture*			endLevel_tex = NULL;
SDL_Texture*			spike_tex = NULL;

SDL_Texture*			GUIBase_tex = NULL;
SDL_Texture*			GUILive_tex = NULL;

SDL_Texture*			fail_tex = NULL;
SDL_Texture*			ball_tex = NULL;

SDL_Texture*			onCheckpoint_tex =NULL;
SDL_Texture*			offCheckpoint_tex = NULL;

SDL_Texture*			onRingRight_tex =NULL;
SDL_Texture*			offRingRight_tex = NULL;
SDL_Texture*			onRingLeft_tex =NULL;
SDL_Texture*			offRingLeft_tex = NULL;

SDL_Texture*			onRingRightHor_tex = NULL;
SDL_Texture*			offRingRightHor_tex = NULL;
SDL_Texture*			onRingLeftHor_tex = NULL;
SDL_Texture*			offRingLeftHor_tex = NULL;
SDL_Texture*			life_tex = NULL;

SDL_Texture* loadTexture(std::string file, SDL_Renderer* renderer) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, file.c_str());
	if(texture != NULL) {
		return texture;
	}
	else {
		std::cout << SDL_GetError() << std::endl;
	}
}

void TextureLoad(SDL_Renderer* renderer) {
	ball_tex = loadTexture("resources/ball.png", renderer);
	wall_tex = loadTexture("resources/wall.png", renderer);
	space_tex = loadTexture("resources/space.png", renderer);
	endLevel_tex = loadTexture("resources/end_level.png", renderer);

	spike_tex = loadTexture("resources/spike.png", renderer);

	life_tex = loadTexture("resources/life.png", renderer);

	GUIBase_tex = loadTexture("resources/GUI/GUIBase.png", renderer);
	GUILive_tex = loadTexture("resources/GUI/GUILive.png", renderer);
	gameover_tex = loadTexture("resources/GUI/gameover.png", renderer);

	fail_tex = loadTexture("resources/fail.png", renderer);

	onCheckpoint_tex = loadTexture("resources/checkpointActive.png", renderer);
	offCheckpoint_tex = loadTexture("resources/checkpoint.png", renderer);
	
	onRingRight_tex = loadTexture("resources/rings/ringA_right.png", renderer);
	offRingRight_tex = loadTexture("resources/rings/ringB_right.png", renderer);
	onRingLeft_tex = loadTexture("resources/rings/ringA_left.png", renderer);
	offRingLeft_tex = loadTexture("resources/rings/ringB_left.png", renderer);

	onRingRightHor_tex = loadTexture("resources/ring_hor/ringA_right.png", renderer);
	offRingRightHor_tex = loadTexture("resources/ring_hor/ringB_right.png", renderer);
	onRingLeftHor_tex = loadTexture("resources/ring_hor/ringA_left.png", renderer);
	offRingLeftHor_tex = loadTexture("resources/ring_hor/ringB_left.png", renderer);
}

void SpriteTextureDestructor(){}