#include <hge.h>

#include "VPolygon.h"

#pragma comment(lib, "hge.lib")
#pragma comment(lib, "hgehelp.lib")

HGE       * hge;
VMPolygon p;
VMPolygon p2;

bool FrameFunc()
{
  return false;
}

bool RenderFunc()
{
  hge->Gfx_BeginScene();
  hge->Gfx_Clear(ARGB(255,0,0,0));
  float mx,my;
  hge->Input_GetMousePos(&mx, &my);
  if(p.IsIntersect(&p2, false)) hge->Gfx_Clear(ARGB(255,55,0,100));

  int i;
  for(i=0;i<p.VerticesCount()-1;i++)
    hge->Gfx_RenderLine(p.GetVertice(i).x, p.GetVertice(i).y, p.GetVertice(i+1).x, p.GetVertice(i+1).y);
  hge->Gfx_RenderLine(p.GetVertice(p.VerticesCount()-1).x, p.GetVertice(p.VerticesCount()-1).y, p.GetVertice(0).x, p.GetVertice(0).y);

  for(i=0;i<p2.VerticesCount()-1;i++)
    hge->Gfx_RenderLine(p2.GetVertice(i).x, p2.GetVertice(i).y, p2.GetVertice(i+1).x, p2.GetVertice(i+1).y, ARGB(255,0,0,255));
  hge->Gfx_RenderLine(p2.GetVertice(p2.VerticesCount()-1).x, p2.GetVertice(p2.VerticesCount()-1).y, p2.GetVertice(0).x, p2.GetVertice(0).y, ARGB(255,0,0,255));

  hge->Gfx_EndScene();

  p.Reset();
  p.Translate(-400.f,-300.f);
  p.Translate(mx,my);

  p2.Reset();
  p2.Translate(-120,-300);
  p2.Rotate(hge->Timer_GetTime());
  p2.Translate(120,300);

 
  return false;
}



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  hge = hgeCreate(HGE_VERSION);
  if(hge==NULL)
  {
    return -1;
  }


  hge->System_SetState(HGE_LOGFILE, "test.log");
  hge->System_SetState(HGE_TITLE, "test");
  hge->System_SetState(HGE_WINDOWED, true);
  hge->System_SetState(HGE_USESOUND, false);
  hge->System_SetState(HGE_SCREENWIDTH, 800);
  hge->System_SetState(HGE_SCREENHEIGHT, 600);
  hge->System_SetState(HGE_FPS, 60);
  hge->System_SetState(HGE_HIDEMOUSE, false);
  hge->System_SetState(HGE_SHOWSPLASH, false);
  hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
  hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);

  if(hge->System_Initiate())
  {

    float k;
    for(k=0;k<3.14*2.0f;k+=3.14*2.0/140.0f)
      p.AddVertice(VPoint2D(400+cos(k)*(50.0f+sinf(k*7.0f)*0.0f),300+sin(k)*(70.0f+sinf(k*7.0f)*0.0f)));

    for(k=0;k<3.14*2.0f;k+=3.14*2.0/140.0f)
      p2.AddVertice(VPoint2D(120+cos(k)*(200.0f+sinf(k*3.0f)*80.0f),300+sin(k)*(100.0f+sinf(k*3.0f)*80.0f)));

    p.Reset();
    p2.Reset();
    hge->System_Start();
  }
  else return -1;

  

  hge->Release();

  return 0;
}