#include "painter.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "ring.h"

using namespace std;

Painter::Painter(SDL_Renderer* renderer) {
	this->renderer = renderer;
	setCamera();

	for(int i = 0; i < 32; i++) {
		textures[i] = NULL;
	}
}

SDL_Texture* Painter::loadTexture(string name) {
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, name.c_str());
	if(texture != NULL) {
		return texture;
	}
	else {
		std::cout << SDL_GetError() << std::endl;
	}
}

void Painter::drawTexture(SDL_Texture* texture, float x, float y, float angle) {
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopyEx(renderer, texture, NULL, &pos, angle, NULL, SDL_FLIP_NONE);
}

void Painter::rotateTexture(SDL_Texture* texture, SDL_Texture* target, float angle) {
	SDL_Rect pos;
	pos.x = 15; 
	pos.y = 25;

	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);

	if(target == NULL)
		SDL_Texture *target = SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA4444, SDL_TEXTUREACCESS_TARGET,  pos.w, pos.h);
   //Set the target texture for rendering
   	SDL_SetRenderTarget( renderer, target );
   //Render m_texture to the target texture with an angle
   	SDL_RenderCopyEx( renderer, texture, NULL, &pos, angle, NULL, SDL_FLIP_NONE );
   //Detach the target texture
   	SDL_SetRenderTarget( renderer, NULL );
   //Save texture
}

void Painter::clear() {
	SDL_RenderClear(renderer);
}

void Painter::present() {
	SDL_RenderPresent(renderer);
}

void Painter::setCamera(Camera* camera) {
	this->camera = camera;
}

Camera* Painter::getCamera() {
	return camera;
}

void Painter::initTextures() {
	textures[0] = loadTexture("resources/ball.png");
	textures[1] = loadTexture("resources/bigBall.png");
	textures[2] = loadTexture("resources/fail.png");
	
	textures[3] = loadTexture("resources/wall0.png");
	
	textures[4] = loadTexture("resources/space.png");

	textures[5] = loadTexture("resources/portalActive.png");
	textures[6] = loadTexture("resources/portalLocked.png");

	textures[7] = loadTexture("resources/spike.png");

	textures[8] = loadTexture("resources/life.png");

	textures[9] = loadTexture("resources/checkpointActive.png");
	textures[10] = loadTexture("resources/checkpoint.png");

	textures[11] = loadTexture("resources/smallOn.png");
	textures[12] = loadTexture("resources/smallOff.png");

	textures[13] = loadTexture("resources/bigOn.png");
	textures[14] = loadTexture("resources/bigOff.png");

	textures[15] = loadTexture("resources/guiBase.png");
	textures[16] = loadTexture("resources/guiLife.png");
	textures[17] = loadTexture("resources/guiRing.png");

	textures[18] = loadTexture("resources/spider.png");

	textures[19] = loadTexture("resources/wall1.png");
	textures[20] = loadTexture("resources/wall2.png");
	textures[21] = loadTexture("resources/wall3.png");
	textures[22] = loadTexture("resources/wall4.png");

	textures[23] = loadTexture("resources/pump1.png");
	textures[24] = loadTexture("resources/pump2.png");

	textures[25] = loadTexture("resources/water.png");
	textures[26] = loadTexture("resources/jumpWall.png");

	textures[27] = loadTexture("resources/bonus1v2.2.png");
	textures[28] = loadTexture("resources/bonus2.png");
	textures[29] = loadTexture("resources/bonus3.png");

	textures[30] = loadTexture("resources/jumpWall1.png");
	textures[31] = loadTexture("resources/jumpWall2.png");
	textures[32] = loadTexture("resources/jumpWall3.png");
	textures[33] = loadTexture("resources/jumpWall4.png");
}

void Painter::initFonts() {
	mainFont = TTF_OpenFont("resources/fonts/36daysag.ttf", 28);
	if(mainFont == NULL) {
		cout << "Font is not loaded" << endl;
	}
}

void Painter::drawBall(float x, float y, bool isBig, bool isKilled) {
	SDL_Texture* texture;

	{
		if(isBig) 
			texture = textures[1];
		else
			texture = textures[0];
	
		if(isKilled)
			texture = textures[2];
	}

	drawTexture(texture, x - camera->x, y - camera->y);
}

void Painter::drawWall(float x, float y, int type) {
	SDL_Texture* texture; 

	if(type == 0) {
		texture = textures[3];
	}
	if(type != 0) {
		texture = textures[18 + type];
	}

	drawTexture(texture, x - camera->x, y - camera->y);
}

void Painter::drawSpace(float x, float y) {
	drawTexture(textures[4], x - camera->x, y - camera->y);
}

void Painter::drawWater(float x, float y) {
	drawTexture(textures[25], x - camera->x, y - camera->y);
}

void Painter::drawPortal(float x, float y, bool isActivated) {
	SDL_Texture* texture;

	{
		if(isActivated) 
			texture = textures[5];
		else
			texture = textures[6];
	}

	drawTexture(texture, x - camera->x, y - camera->y);
}

void Painter::drawSpike(float x, float y, int directionId) {
	float angle = 0;

	if(directionId == 17)
		angle = 0;
	if(directionId == 18)
		angle = 90;
	if(directionId == 27)
		angle = -90;
	if(directionId == 28)
		angle = 180;


	drawTexture(textures[7], x - camera->x, y - camera->y, angle);
}

void Painter::drawSpider(float x, float y, int numnerOfpart) {
	drawTexture(textures[18], x - camera->x, y - camera->y);
}

void Painter::drawLife(float x, float y) {
	drawTexture(textures[8], x - camera->x, y - camera->y);
}

void Painter::drawCheckpoint(float x, float y, bool isActivated) {
	SDL_Texture* texture;

	{
		if(isActivated) 
			texture = textures[9];
		else
			texture = textures[10];
	}

	drawTexture(texture, x - camera->x, y - camera->y);
}

void Painter::drawRing(float x, float y, bool isBig, bool isRight, bool isVert, bool active) {
	SDL_Texture* texture;

	if(!isBig) {
		if(active)
			texture = textures[11];
		else
			texture = textures[12];
	}
	else
		if(active)
			texture = textures[13];
		else
			texture = textures[14];

	float angle = 0;
	// b2Vec2	shift = b2Vec2(0.0f, 0.0f);
	if(isRight)
		angle += 180;
	else
		angle += 0;

	if(!isVert) {
		angle += 90;
	}

	drawTexture(texture, x - camera->x, y - camera->y, angle);
}

void Painter::drawPump(float x, float y, bool inflator, int directionId) {
	SDL_Texture* texture;

	{
		if(inflator) 
			texture = textures[23];
		else
			texture = textures[24];
	}

	float angle = 0;

	if(directionId == 17)
		angle = 0;
	if(directionId == 18)
		angle = 90;
	if(directionId == 27)
		angle = -90;
	if(directionId == 28)
		angle = 180;

	drawTexture(texture, x - camera->x, y - camera->y, angle);
}

void Painter::drawJumpWall(float x, float y, int type) {
	SDL_Texture* texture; 

	if(type == 0) {
		texture = textures[26];
	}
	if(type != 0) {
		texture = textures[30 + type];
	}

	drawTexture(texture, x - camera->x, y - camera->y);
	// drawWall(x, y, 0);
}

void Painter::drawBonus(float x, float y, int bonusTypeId,  int directionId) {
	SDL_Texture* texture;

	{
		if(bonusTypeId == 1) 
			texture = textures[27];
		else if(bonusTypeId == 2)
			texture = textures[28];
		else
			texture = textures[29];
	}

	float angle = 0;

	if(directionId == 17)
		angle = 0;
	if(directionId == 18)
		angle = 90;
	if(directionId == 27)
		angle = -90;
	if(directionId == 28)
		angle = 180;

	drawTexture(texture, x - camera->x, y - camera->y, angle);
}

void Painter::drawText(float x, float y, string text, int r, int g, int b) {
	SDL_Color color = {r, g, b};
	// color.r = r;
	// color.g = g;
	// color.b = b;
	SDL_Surface* message = NULL;
	SDL_Texture* texture = NULL;

	message = TTF_RenderText_Solid(mainFont, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, message);

	drawTexture(texture, x, y);
}

void Painter::drawGuiBase(float x, float y){
	drawTexture(textures[15], x, y);
}
void Painter::drawGuiLive(float x, float y){
	drawTexture(textures[16], x, y);
}
void Painter::drawGuiRing(float x, float y){
	drawTexture(textures[17], x, y);
}

void Painter::drawMenuBackgound() {
	drawTexture(textures[34], 0, 0);
}

void Painter::drawMenuItemSelector(float x, float y) {
	drawTexture(textures[35], x, y);
}