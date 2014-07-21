#ifndef PAINTER
#define PAINTER

// #include "sprite.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "camera.h"

using namespace std;

class Painter {
	SDL_Renderer*	renderer;
	Camera*			camera;

	SDL_Texture* 		textures[36];
	TTF_Font*			mainFont;
	//Ball:  	2 textures 			[0..1]
	//Wall:		5 textures //TODO 	[2] & [19..22]
	//Space: 	1 textures 			[3]
	//Portal:   2 textures 			[4..5]
	//Spike:  	1 textures 			[6]
	//Life:  	1 textures 			[7]
	//Checkpoint:  	2 textures 		[8..9]
	//Ring:		4 textures 			[10..14]
	//GUI: 		3 textures 			[15..17]
	//Spider:	1 textures 			[18]
	//Pump:		2 textures 			[23..24]
	//Water:	1 textures			[25]
	//JumpWall	5 textures 			[26] & [30..33]
	//Bonuses:	3 textures 			[27..29]
	//Menu:		2 textures 			[34..35]


	SDL_Texture* 	loadTexture(string nameOfTexture);


	void 			drawTexture(SDL_Texture* texture, float x, float y, float angle = 0);
	void			rotateTexture(SDL_Texture* texture, SDL_Texture* target,float angle);
public:
	Painter(SDL_Renderer* renderer);

	void 		clear();
	void		present();

	void		setCamera(Camera* camera = NULL);
	Camera*		getCamera();
	
	void 		initTextures();
	void 		initFonts();

	void 		drawBall(float x, float y, bool isBig, bool isKilled);
	void 		drawWall(float x, float y, int type);
	void 		drawSpace(float x, float y);
	void 		drawWater(float x, float y);
	void 		drawPortal(float x, float y, bool isActivated);
	void 		drawSpike(float x, float y, int directionId);
	void 		drawLife(float x, float y);
	void 		drawCheckpoint(float x, float y, bool activated);
	void 		drawRing(float x, float y, bool isBig, bool isRight, bool isVert, bool active);
	void 		drawSpider(float x, float y, int partNumber);
	void 		drawPump(float x, float y, bool inflator, int directionId);
	void 		drawJumpWall(float x, float y, int type);
	void 		drawBonus(float x, float y, int bonusTypeId, int directionId);

	void 		drawText(float x, float y, string text, int r, int g, int b);

	void 		drawGuiBase(float x, float y);
	void 		drawGuiLive(float x, float y);
	void 		drawGuiRing(float x, float y);

	void 		drawMenuBackground();
	void 		drawMenuItemSelector(float x, float y);
};

#endif