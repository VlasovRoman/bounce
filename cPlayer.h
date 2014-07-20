#include <vector>

#include "cWall.h"
#include "CollisionDetection.h"

#ifndef H_CLASS_PLAYER
#define H_CLASS_PLAYER

class cPlayer:public cBall
{
protected:
    float fDX, fDY;
    float fSpeed;
    float fJumpSpeed;
    float fZX, fZY;
    float fFriction;
	float fCollX, fCollY;
	short int iLive;
public:
	friend class cGame;
	cPlayer();
	cPlayer(float _x, float _y):cBall(_x, _y, 16)
	{
		fDX = 0, fDY = 0;
		fSpeed = 10, fJumpSpeed = 5;
		fZX = 0, fZY = 0;
		fFriction = 0.98;
		iLive = 3;
	}

	void vContrJump() { fDY = -fJumpSpeed; }
	void vContrLeft(float dt) { fDX -= fSpeed * dt; }
	void vContrRight(float dt) { fDX += fSpeed * dt; }

	void vCollDX() { fDX = -fDX / 4; fDY = fDY; x = fZX; }
	void vCollDY() { fDY = -fDY / 4; }

	void vVelocityFrame(float dt)
	{
		fDY = (fDY + 9.81 * dt) * fFriction;
		fDX *= fFriction;
	}

	void vMoveFrame()
	{
		x += fDX; 
		y += fDY;
	}

	void vPointRecY() { y = fZY; }
	void vPointRec() { y = fZY; x = fZX;}
	void vPointRet() { fZY = y; fZX = x; }
};

#endif H_CLASS_PLAYER
 
