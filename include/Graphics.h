#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "Constants.h"

//
//      ENGINE AND HARDWARE
//

void VSync();
void ClearScreen();
void DrawPixel(uint x, uint y, ushort col);
ushort GetPixel(uint x, uint y);

//
//      COLORFUL MODE FUNCTIONS
//

ushort ColorIncrease(ushort col);
ushort ColorDecrease(ushort col);
ushort ColorAdvance(ushort col, int _switch);
int SetSwitch(ushort col, int _switch);

#endif