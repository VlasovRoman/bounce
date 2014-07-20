#include "hge.h"
#include "hgefont.h"
#include "hgegui.h"
#include "hgesprite.h"

#include "levels.h"
#include "cPlayer.h"
#include "cWall.h"

#include <vector>

#ifndef H_CLASS_GAME
#define H_CLASS_GAME

HGE *hge = 0;
cPlayer Player(0, 0);
cRect* cLevelEnd;

cCollisionDetection ColDet;

class cGame
{	
protected:
	int map[100][100]; //����������� �����. 
	int iLevel; //������������� ������
	int iFailFrame; //���-�� "������" ������ �� ����� ������
	int iFailCount; //���������� ��� "������������� �������� �������� �� ����� ������
	bool bFail; //��������� �������� ��������(True = ������)
	bool bGameOver; //���������� ��� ����������� ������� GameOver
	float fFailX, fFailY; //���������� ������
	int iMapInitX, iMapInitY; //���������� ��� ������������� �����
	bool bLoadLevel; //���������� �������� �����
	bool bDeath;
	std::vector<cWall> vecWalls; //������ ����
	std::vector<cPoly> vecChip; //������ �����
public:
	friend class cPlayer;
	cGame()
	{
		//������������� �����
		for(int i = 0; i < 100; i++)
			for(int ii = 0; ii < 100; ii++)
				map[i][ii] = 0;

		iLevel = 0; //����� ID ������ ������� 0, ���-��� ������� load_lvl ���������� � ���� +1 � ������ ����� � ���������
		bFail = false;
		bGameOver = false;
		iFailFrame = 100;
		bLoadLevel = false;
		iFailCount = 0;
		bDeath = false;
	}
	
	//������ �����
	void map_render()
	{	
		for (int xx = 0; xx < iMapInitX; xx++)
	    {
		    for (int yy = 0; yy < iMapInitY; yy++)
		    {
    			switch (map[(int)yy][(int)xx])
			    {
				case 0: space_spt->Render(xx * 32, yy * 32); break;
				case 1: wall_spt->Render(xx * 32 + 16, yy * 32 + 16); break;
				case 2: Player.x = xx * 32; Player.y = yy * 32; map[(int)yy][(int)xx] = 0; space_spt->Render(xx * 32, yy * 32); break;
				case 3: endLevel_spt->Render(xx * 32, yy * 32); break; 
				case 4: space_spt->Render(xx * 32, yy * 32); boom_spt->Render(xx * 32, yy * 32); break;
			    }
		    }
	    }
	}

	//������ �������(������ ������)
	void sprite_render()
	{
		//����� ������ ��� �� ������ ��������:
		if(bFail == false) 
			ball_spt->Render(Player.fX(), Player.fY()); //���� �� ����, �� �� �������� ������ �����
		else //���� �� �� ������
		{
			if(bGameOver) 
				gameover_spt->Render(0, 160); //���� �� ������ ����� � ��� �� ���� ������, �� �� �������� GameOver
			else
				fail_spt->Render(fFailX, fFailY); //����� �� ������ "�����"
		}
	}

	//������ ����������
	void GUI_render()
	{
		GUIBase_spt->Render(0, 320); 
	    GUILive_spt->Render(3.5, 323.5);
	    fnt->printf(32, 323.5, HGETEXT_LEFT, "x %d", Player.iLive);
	}

	void death()
	{
		//���������� ���������� ���� � ������ ������
		fFailX = Player.fX() - 16;
		fFailY = Player.fY() - 16;
		//�������� ��������
		Player.fDX = 0;
		Player.fDY = 0;
		Player.iLive--; //�������� ���� �����
		//���� � ��� 0 ������, �� �� ������������� ���������� bGameOver �� �����, 
		//ID ������ ������������� �� 0 � ��������������� ������� ������
		if(Player.iLive == 0)
		{
		    bGameOver = true;
		    iLevel = 0;
		    Player.iLive = 3;
		}
		else
			iLevel--;	//���� �� � ��� ���� � �����, �� ������ �� ��������
		bDeath = false;
		LoadLevel(); //������������� �������		
	}

	//������� �����
	void frame(float dt)
	{	
		if(bFail == false) //���� �� ����
		{
		    move(dt); //�� ����������� ����������� ����
			if(bDeath)
				death();
		}
		else 
		{   //��� ������� ���� ������� ������. � ��� ���� ���������� iFailCount, ������������ ������� ��������(��� ������) 
		    //�� "������ �� ������". ����� ��� ���������� ����� ���������� "������ ������", 
		    //�� ������������� bFail �� ������� � �������� iFailCount. ��� ��������� ������� ����� ��� ������ ������ ������� �����.
		    iFailCount++; 
		    if(iFailCount == iFailFrame)
		    {
			    bFail = false;
			    iFailCount = 0;
		    }
		}
	}
	
	void render()
	{
		map_render();
		sprite_render();
		GUI_render();
	}

	 void move(float dt)
	{
		if(hge->Input_GetKeyState(HGEK_LEFT)) {Player.vContrLeft(dt);}
		if(hge->Input_GetKeyState(HGEK_RIGHT)) {Player.vContrRight(dt);}
		collision();
		Player.vVelocityFrame(dt); 
		Player.vPointRet();
		Player.vMoveFrame();
	}

	void collision()
	{
		cBall Ball(Player.fX(), Player.fY(), Player.radius());
		for(std::vector<cWall>::iterator i = vecWalls.begin(); i != vecWalls.end(); i++)
		{
			cRect Wall(i->fX(), i->fY(), -16, -16, 16, 16);
			switch (ColDet.IsCollision(&Ball, &Wall))
			{
			case 0: {} break;
			case 1: 
				if(hge->Input_GetKeyState(HGEK_UP)) 
				{
					Player.vContrJump(); 
					break;
				} 
				Player.vCollDY(); 
				if(fabs(Player.fDY) <= 0.05) 
					Player.vPointRecY();
				break;
			case 2: Player.vCollDX(); break;
			case 3: Player.vCollDY();  Player.vPointRecY(); break;
			case 4: Player.vCollDX(); break;
			}
		}

		if(ColDet.IsCollision(&Ball, cLevelEnd))
			LoadLevel();

		for(std::vector<cPoly>::iterator i = vecChip.begin(); i != vecChip.end(); i++)
		{
			cPoly Chip(i->fX(), i->fY(), 0.0f, -8.0f, 8.0f, 16.0f, -8.0f, 16.0f);
			if(ColDet.IsCollision(&Ball, &Chip))
			{
				bDeath = true;
				bFail = true;
			}
				
		}
	}

	void LoadLevel()
	{
		Player.fDX = 0;
		Player.fDY = 0;
		iLevel++;
		for (int mx = 0; mx < 10; mx++) for (int my = 0; my < 10; my++) map[my][mx] = 0; //������� ����. �����
		//��������� �������
	    if(iLevel > 3)
		    iLevel = 1;
		//
	    switch (iLevel)
	    {
	    case 1: iMapInitY = lvl_y; iMapInitX = lvl_x; for (int mx = 0; mx < iMapInitX; mx++) for (int my = 0; my < iMapInitY; my++) map[my][mx] = level1[my][mx]; break;
	    case 2: iMapInitY = lvl_y; iMapInitX = lvl_x; for (int mx = 0; mx < 10; mx++) for (int my = 0; my < 10; my++) map[my][mx] = level2[my][mx]; break;
        case 3:	iMapInitY = lvl_y; iMapInitX = lvl_x; for (int mx = 0; mx < 10; mx++) for (int my = 0; my < 10; my++) map[my][mx] = level3[my][mx]; break;
	    }

		vecWalls.clear();
		vecChip.clear();

		for(int ix = 0; ix < iMapInitX; ix++)
		{
			for(int iiy = 0; iiy < iMapInitY; iiy++)
			{
				switch(map[iiy][ix])
				{
				case 1:
					{
					    cWall Walls(ix * 32 + 16, iiy * 32 + 16);
					    vecWalls.push_back(Walls);
					} break;
				case 3: cLevelEnd = new cRect((float)ix * 32 + 16, iiy * 32 + 16, -16, -16, 16, 16); break;
				case 4:
					{
					    cPoly _Chip((float)ix * 32 + 16,(float) iiy * 32 + 16, 0, -13, +8, +16, -8, +16);
					    vecChip.push_back(_Chip);
					} break;
				}
			}
		}
		bLoadLevel = false;
    }
};

#endif H_CLASS_GAME