#include "Input.h"
#include "Graphics.h"
#include "Constants.h"

//Constants
#define MAX_COLORS 9
const ushort COLORS[] =
{
    0x7FFF,     //WHITE
    0x1F,       //COLORFUL MODE
    0x1F,       //RED
    0x3e0,      //GREEN
    0x7C00,     //BLUE
    0x3FF,      //YELLOW
    0x7C1F,     //MAGENTA
    0x7FE0,     //CYAN
    0x2108,     //GREY
};
#define MAX_CURSOR_COLORS 5
const ushort CURSOR_COLORS[] =
{
    1,          //CURRENT COLOR
    0x7C11,     //BLUE
    0x11F,      //RED
    0x7FFF,     //WHITE
    0           //BLACK
};

ushort DrawConditions(int x, int y, ushort color, int color_mode, int color_switch)
{
  ushort c = color;
  //If B is not pressed, draw
  if(!GetKeyDown(INPUT_B)) 
  {
    //If Color mode is the one for Colorful mode, do some weird color magic that doesn't work as intended
    if(color_mode == 1) c = ColorAdvance(color, color_switch);

    //Drawing the pixel to VRAM
    DrawPixel(x, y, c);
  }
  return c;
}

int main()
{
  VIDEO_MODE = MODE_3;

  ushort CurrentColor = 0x7FFF;
  ushort PreviousColor = CurrentColor;

  uint x = 120, y = 80;
  int ColorMode   = 0;
  int ColorSwitch = 1;
  
  int Last_Start = 0;
  int Last_L     = 0;
  int Last_R     = 0;

  int CursorMode = 0;  
  ushort CursorColor = CurrentColor;

  while(1)
  {
    VSync();
    InputPoll();

    DrawPixel(x, y, PreviousColor);

    //Moving the cursor and doing some conditions
    if(GetKeyDown(INPUT_UP) && y > 0)
    {
      y--;
      CurrentColor = DrawConditions(x, y, CurrentColor, ColorMode, ColorSwitch);
    }

    if(GetKeyDown(INPUT_DOWN) && y < 160-1)
    {
      y++;      
      CurrentColor = DrawConditions(x, y, CurrentColor, ColorMode, ColorSwitch);
    }

    if(GetKeyDown(INPUT_LEFT) && x > 0)
    {
      x--;
      CurrentColor = DrawConditions(x, y, CurrentColor, ColorMode, ColorSwitch);
    }

    if(GetKeyDown(INPUT_RIGHT) && x < 240-1)
    {
      x++;
      CurrentColor = DrawConditions(x, y, CurrentColor, ColorMode, ColorSwitch);
    }

    //Clearing the screen
    if(GetKeyDown(INPUT_SELECT))
    {
      ClearScreen();
    }

    //Cycling through cursor colors
    if(!GetKeyDown(INPUT_START) && Last_Start)
    {
      if(CursorMode>=MAX_CURSOR_COLORS-1)
      {
        CursorMode = 0;
      }
      else CursorMode++;
      CursorColor = CURSOR_COLORS[CursorMode];
    }

    //Moving through colors
    if(!GetKeyDown(INPUT_L) && Last_L)
    {
      if(ColorMode<=0)
      {
        ColorMode = MAX_COLORS-1;
      }
      else ColorMode--;
      CurrentColor = COLORS[ColorMode];
    }

    if(!GetKeyDown(INPUT_R) && Last_R)
    {
      if(ColorMode>=MAX_COLORS-1)
      {
        ColorMode = 0;
      }
      else ColorMode++;
      CurrentColor = COLORS[ColorMode];
    }

    //Setting previous states of these buttons
    Last_Start = GetKeyDown(INPUT_START); 
    Last_L     = GetKeyDown(INPUT_L);
    Last_R     = GetKeyDown(INPUT_R);

    //Weird function for drawing in colorful mode
    SetSwitch(CurrentColor, ColorSwitch);

    //Saving the information of this pixel, since cursor is going to draw on top of it
    PreviousColor = GetPixel(x, y);
    
    //Cursor mode 0 is just the CurrentCollor
    if(CursorMode == 0) CursorColor = CurrentColor;

    //Drawing the cursor
    DrawPixel(x, y, CursorColor);
  }
  return 0;
}
