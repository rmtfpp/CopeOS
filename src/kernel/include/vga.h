#ifndef __VGA_H
#define __VGA_H

#include "math.h"
#include "system.h"

#define VGA_MAX_ROWS	25
#define VGA_MAX_COLUMNS 80

extern void cls();
extern void putc(uint8_t c);
extern void puts(uint8_t* text);
extern void settextcolor(uint8_t forecolor, uint8_t backcolor);
extern void init_video(void);
extern void puti(int32_t num);
extern void putx(uint32_t num);

#endif
