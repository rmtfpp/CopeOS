#ifndef __STRING_H
#define __STRING_H

#include "cdefs.h"

extern void*	 memcpy(void* to, const void* from, size_t count);
extern uint8_t*	 memset(uint8_t* dest, uint8_t val, size_t count);
extern uint16_t* memsetw(uint16_t* dest, uint16_t val, size_t count);
extern size_t	 strlen(const uint8_t* str);
extern uint8_t*	 itoa(int32_t number, uint8_t* arr, size_t base);
extern void	 strrev(uint8_t* arr, int32_t start, int32_t end);

#endif
