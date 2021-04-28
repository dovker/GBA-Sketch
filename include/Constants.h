#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define uint            unsigned int
#define ushort          unsigned short

#define VIDEO_MODE      *(uint*)0x4000000
#define VRAM            ((ushort*)0x6000000)
#define MODE_3          0x403
#define REG_VCOUNT      *(volatile ushort*)0x04000006

#define INPUT_MEMORY    (*(uint*)0x4000130)
#define INPUT_MASK      0xFC00

#define INPUT_LEFT      0x0020
#define INPUT_RIGHT     0x0010
#define INPUT_UP        0x0040
#define INPUT_DOWN      0x0080
#define INPUT_SELECT    0x0004
#define INPUT_START     0x0008
#define INPUT_A         0x0001
#define INPUT_B         0x0002
#define INPUT_L         0x0200
#define INPUT_R         0x0100


#endif