#include <math.h>

#ifndef H_COLLISION_DETECTION
#define H_COLLISION_DETECTION

class PointXY
{
public:
	float x, y;
	PointXY(float _x, float _y)
	{
		x = _x, y = _y;
	}
	PointXY()
	{
		x = 0; y = 0;
	}
};

class Object
{
protected:
	float x, y; //Координаты объекта
public:
	friend class CollisionDetection;
	Object();
	Object(float _x, float _y)
	{
		x = _x;	y = _y;
	}
	
	void control(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	float fX()
	{
		return x;
	}

	float fY()
	{
		return y;
	}
};

class cBall : public Object
{
	float r;
public:
	friend class Object;
	cBall(float _x, float _y, float _r) : Object(_x, _y)
	{ 
		r = _r;
	}

	float radius()
	{
		return r;
	}	
};

class cLine:public PointXY
{
	static const int lineN = 1;
	PointXY point_1;
	PointXY point_2;
public:
	cLine(){};
	cLine(float x1, float y1, float x2, float y2)
	{
		point_1.x = x1;
		point_1.y = y1;
		point_2.x = x2;
		point_2.y = y2;
	}

	cLine(PointXY* _point_1, PointXY* _point_2)
	{
		point_1.x = _point_1->x;	
		point_1.y = _point_1->y;	
		point_2.x = _point_2->x;	
		point_2.y = _point_2->y;	
	}

	float x1(){ return point_1.x;}

	float y1(){ return point_1.y;}

	float x2(){ return point_2.x;}

	float y2(){ return point_2.y;}
};

class cRect : public Object
{
	static const int lineN = 4;
public:
	PointXY RectPoint[4];
	cLine   Lines[4];

	friend class CollisionDetection;

	cRect();
	cRect(float _x, float _y, float x1, float y1, float x2, float y2) : Object(_x, _y)
	{
		RectPoint[0] = PointXY(_x + x1,_y + y1);
		RectPoint[1] = PointXY(_x + x2,_y + y1);
		RectPoint[2] = PointXY(_x + x2,_y + y2);
		RectPoint[3] = PointXY(_x + x1,_y + y2);

		Lines[0] = cLine(&RectPoint[0], &RectPoint[1]);
		Lines[1] = cLine(&RectPoint[1], &RectPoint[2]);
		Lines[2] = cLine(&RectPoint[2], &RectPoint[3]);
		Lines[3] = cLine(&RectPoint[3], &RectPoint[0]);
	}


};

class cPoly
{
	float x, y;
	//int lineN;
public:
	PointXY Points[100];
	cLine Lines[100];

	cPoly() {}

	cPoly(float _x, float _y, float x1, float y1, float x2, float y2, float x3, float y3)
	{
		x = _x;
		y = _y;

		Points[0] = PointXY(x + x1, y + y1);
		Points[1] = PointXY(x + x2, y + y2);
		Points[2] = PointXY(x + x3, y + y3);

		Lines[0] = cLine(&Points[0], &Points[1]);
		Lines[1] = cLine(&Points[1], &Points[2]);
		Lines[2] = cLine(&Points[2], &Points[0]);
	}

	float fX(){ return x;}
	float fY(){ return y;}
};

class cCollisionDetection
{
public:
	bool IsCollision(cBall* _Ball, cBall* __Ball)
	{
		float dx = fabs((double)_Ball->fX() - __Ball->fX());
		float dy = fabs((double)_Ball->fY() - __Ball->fY());
		float gip = sqrt(dx * dx + dy * dy);
		float min_rad = _Ball->radius() + __Ball->radius();

		if(min_rad <= gip)
			return true;
		else
			return false;
	}

	bool IsCollision(cBall* _Ball, cLine* _Line)
	{
		//Спасибо юзеру BetaUser с GameDev.ru за предоставление кода.
		float x01=_Line->x1()-_Ball->fX();
		float y01=_Line->y1()-_Ball->fY();
		float x02=_Line->x2()-_Ball->fX();
		float y02=_Line->y2()-_Ball->fY();

		float dx=x02-x01;
		float dy=y02-y01;

		float a=dx*dx+dy*dy;
		float b=2.0f*(x01*dx+y01*dy);
	    float c=x01*x01+y01*y01-_Ball->radius()*_Ball->radius();

	    if(-b<0)return (c<0);
	    if(-b<(2.0f*a))return (4.0f*a*c-b*b<0);
	    return (a+b+c<0);
	}

	int IsCollision(cBall* _Ball, cRect* _Rect)
	{
		if(IsCollision(_Ball, &_Rect->Lines[0])) 	return 1;
		if(IsCollision(_Ball, &_Rect->Lines[1])) 	return 2;
		if(IsCollision(_Ball, &_Rect->Lines[2])) 	return 3;
		if(IsCollision(_Ball, &_Rect->Lines[3])) 	return 4;
		else return 0;
	}

	bool IsCollision(cBall* _Ball, cPoly* _Poly)
	{
		if(IsCollision(_Ball, &_Poly->Lines[0])) 	return true;
		if(IsCollision(_Ball, &_Poly->Lines[1])) 	return true;
		if(IsCollision(_Ball, &_Poly->Lines[2])) 	return true;
		else return false;
	}
};

extern cCollisionDetection ColDet;

#endif H_COLLISION_DETECTION

