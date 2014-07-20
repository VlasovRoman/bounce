#include "hge.h"

#include "ResInit.h"
#include "cGame.h"

cGame Game;

bool FrameFunc()
{
	float dt=hge->Timer_GetDelta(); //получаем дельту времени
	Game.frame(dt);
	return false;
}

bool RenderFunc()
{
	//Рендер графики
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	Game.render();
	hge->Gfx_EndScene();

	return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "bounce_log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Bounce: Remake");
	hge->System_SetState(HGE_FPS, 100);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 320);
	hge->System_SetState(HGE_SCREENHEIGHT, 384);
	hge->System_SetState(HGE_SCREENBPP, 32);

	if(hge->System_Initiate()) 
	{	
		TextureLoad(hge); //Загрузка ресурсов
		SpriteInit(); //Инициализация спрайтов
		Game.LoadLevel(); //Загрузка уровня перед запуском игры
		
		hge->System_Start(); //Запуск движка

		SpriteTextureDestructor(hge); //Удаление созданных спрайтов и очистка ресурсов
	}
	hge->System_Shutdown(); 	// Очистка и закрытие
	hge->Release();
	return 0;
}
