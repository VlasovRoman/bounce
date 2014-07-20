#ifndef RESINIT
#define RESINIT

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

extern SDL_Texture*			ball_tex;
extern SDL_Texture*			wall_tex;
extern SDL_Texture*			space_tex;
extern SDL_Texture*			endLevel_tex;

extern SDL_Texture*			life_tex;

extern SDL_Texture*			onPortal_tex;
extern SDL_Texture*			offPortal_tex;

extern SDL_Texture*			spike_tex;
extern SDL_Texture*			GUIBase_tex;
extern SDL_Texture*			GUILive_tex;
extern SDL_Texture*			fail_tex;
extern SDL_Texture*			gameover_tex;
extern SDL_Texture*			onCheckpoint_tex;
extern SDL_Texture*			offCheckpoint_tex;

extern SDL_Texture*			onRingRight_tex;
extern SDL_Texture*			offRingRight_tex;
extern SDL_Texture*			onRingLeft_tex;
extern SDL_Texture*			offRingLeft_tex;

extern SDL_Texture*			onRingRightHor_tex;
extern SDL_Texture*			offRingRightHor_tex;
extern SDL_Texture*			onRingLeftHor_tex;
extern SDL_Texture*			offRingLeftHor_tex;


extern SDL_Texture* loadTexture(std::string file, SDL_Renderer* renderer);

extern void TextureLoad(SDL_Renderer* renderer);

extern void SpriteTextureDestructor();

#endif