#include <string.h>

uint16_t* memsetw(uint16_t* dest, uint16_t val, size_t count)
{
	uint16_t* original_dest = dest;
	while (count--)
		*dest++ = val;
	return original_dest;
}
