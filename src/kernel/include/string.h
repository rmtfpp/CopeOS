#ifndef __STRING_H
#define __STRING_H

#include "system.h"

void*		       memcpy(void* to, const void* from, size_t count);
uint8_t*	       memset(uint8_t* dest, uint8_t val, size_t count);
extern unsigned short* memsetw(unsigned short* dest, unsigned short val, int count);
extern int	       strlen(const char* str);

#endif
