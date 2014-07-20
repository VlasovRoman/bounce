#ifndef GUI
#define GUI

#include <SDL2/SDL.h>

#include "eventListener.h"
#include "sprite.h"
#include "camera.h"
#include "player.h"

class Gui{
protected:
	SDL_Renderer*		renderer;
	Sprite*				base;
	Sprite*				ring;
	Sprite*				life;
	Sprite*				gameOverMessege;

	Player*				player;
	// int 				killedTimeNow;
	
	int* 				activeRings;
	short int 			lives;
public:
	Gui();
	Gui(SDL_Renderer* renderer);

	void 				initSprites();
	void 				setPlayer(Player* player);
	void				setRingsNumber(int* number);
	// void 			setExplosionTexture(SDL_Texture* texture);
	// void 			setPlayerTexture(SDL_Texture* texture);
	
	// void 			control(EventListener* eventListener);

	// void			setCheckpoint(b2Vec2 position);

	// void 			setOnGround(bool is);

	// void 			birth(bool awake );

	// bool 			getDeath();

	// void 			kill();

	void 			draw(Player *player, int ringsNumber);
};

#endif
 