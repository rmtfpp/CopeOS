#ifndef __VGA_H
#define __VGA_H

#include "system.h"

#define VGA_MAX_ROWS	25
#define VGA_MAX_COLUMNS 80

void scroll(void);
void move_csr(void);
void cls();
void putc(uint8_t c);
void puts(uint8_t* text);
void settextcolor(uint8_t forecolor, uint8_t backcolor);
void init_video(void);

#endif
