#include "Graphics.h"

//
//      ENGINE AND HARDWARE
//

void VSync()
{
  while(REG_VCOUNT >= 160);
  while(REG_VCOUNT < 160);
}
void ClearScreen()
{
  for(int i = 0; i < 240*160; i++)
  {
    VRAM[i] = 0;
  }
}
void DrawPixel(uint x, uint y, ushort col)
{
  VRAM[x+y*240] = col;
}
ushort GetPixel(uint x, uint y)
{
  return VRAM[x+y*240];
}

//
//      SOME FUNKY FUNCTIONS FOR THE COLORFUL MODE
//      DON'T TRY TO UNDERSTAND THEM, THEY DON'T
//      WORK AS EXPECTED HAHA
//

ushort ColorIncrease(ushort col)
{
  ushort c = col;
  if(c >= 0x1F)
  {
    if(c>= 0x3FF)
    {
      c+= 0x3FF;
    }
    c+=0x1F;
  }
  else
  {
    c++;
  }
  return c;
}
ushort ColorDecrease(ushort col)
{
  ushort c = col;
  if(c <= 0x3FF)
  {
    if(c <= 0x1F)
    {
      c--;
    }
    c-=0x1F;
  }
  else
  {
    c-= 0x3FF;
  }
  return c;
}
ushort ColorAdvance(ushort col, int _switch)
{
  ushort c = col;
  if(_switch) return ColorIncrease(c);
  else return ColorDecrease(c);
}
int SetSwitch(ushort col, int _switch)
{
  if(col <= 0x842) return 1;
  else if(col >= 0x7FFF) return 0;
  else return _switch;
}