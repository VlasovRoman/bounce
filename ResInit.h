#include "hgesprite.h"
#include "hgefont.h"

hgeSprite*		ball_spt; 
hgeSprite*		space_spt; 
hgeSprite*		wall_spt;
hgeSprite*		endLevel_spt;
hgeSprite*		boom_spt;
hgeSprite*      GUIBase_spt;
hgeSprite*      GUILive_spt;
hgeSprite*      fail_spt;
hgeSprite*      gameover_spt;

//Инициализация текстур
HTEXTURE			ball_tex;
HTEXTURE			wall_tex;
HTEXTURE			space_tex;
HTEXTURE			endLevel_tex;
HTEXTURE			boom_tex;
HTEXTURE			GUIBase_tex;
HTEXTURE			GUILive_tex;
HTEXTURE			fail_tex;
HTEXTURE			gameover_tex;

hgeFont* fnt;

//Загрузка ресурсов
void TextureLoad(HGE* hge)
{
	ball_tex=hge->Texture_Load("resources/textures/Sprites/ball.png");
	wall_tex=hge->Texture_Load("resources/textures/Sprites/wall.png");
	space_tex=hge->Texture_Load("resources/textures/Sprites/space.png");
	endLevel_tex=hge->Texture_Load("resources/textures/Sprites/end_level.png");
	boom_tex=hge->Texture_Load("resources/textures/Sprites/boom.png");
	GUIBase_tex=hge->Texture_Load("resources/textures/GUI/GUIBase.png");
	GUILive_tex=hge->Texture_Load("resources/textures/GUI/GUILive.png");
	fail_tex=hge->Texture_Load("resources/textures/Sprites/fail.png");
	gameover_tex=hge->Texture_Load("resources/textures/GUI/gameover.png");

	fnt=new hgeFont("resources/fonts/font1.fnt");
}

//Инициализация спрайтов
void SpriteInit()
{
	ball_spt=new hgeSprite(ball_tex, 0, 0, 32, 32);
	ball_spt->SetHotSpot(16,16);

	wall_spt=new hgeSprite(wall_tex, 0, 0, 32, 32);
	wall_spt->SetHotSpot(16, 16);

	space_spt=new hgeSprite(space_tex, 0, 0, 32, 32);
	space_spt->SetHotSpot(0,0);

	endLevel_spt=new hgeSprite(endLevel_tex, 0, 0, 32, 32);
	endLevel_spt->SetHotSpot(0,0);

	boom_spt=new hgeSprite(boom_tex, 0, 0, 32, 32);
	boom_spt->SetHotSpot(0,0);

	GUIBase_spt=new hgeSprite(GUIBase_tex, 0, 0, 320, 64);
	GUIBase_spt->SetHotSpot(0,0);

	GUILive_spt=new hgeSprite(GUILive_tex, 0, 0, 25, 25);
	GUILive_spt->SetHotSpot(0,0);

	fail_spt=new hgeSprite(fail_tex, 0, 0, 32, 32);
	fail_spt->SetHotSpot(0,0);

	gameover_spt=new hgeSprite(gameover_tex, 0, 0, 320, 64);
	gameover_spt->SetHotSpot(0,0);
}

//Выгрузка ресурсов
void SpriteTextureDestructor(HGE* hge)
{
	delete wall_spt;
	delete ball_spt;
	delete space_spt;
	delete endLevel_spt;
	delete boom_spt;
	delete GUIBase_spt;
	delete GUILive_spt;
	delete fail_spt;
	delete gameover_spt;

	hge->Texture_Free(ball_tex);
	hge->Texture_Free(wall_tex);
	hge->Texture_Free(space_tex);
	hge->Texture_Free(endLevel_tex);
	hge->Texture_Free(boom_tex);
	hge->Texture_Free(GUILive_tex);
	hge->Texture_Free(GUIBase_tex);
	hge->Texture_Free(fail_tex);
	hge->Texture_Free(gameover_tex);
}

