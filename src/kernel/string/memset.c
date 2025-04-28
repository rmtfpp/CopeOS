#include <string.h>

uint8_t* memset(uint8_t* dest, uint16_t val, size_t count)
{
	uint8_t* original_dest = dest;
	while (count--)
		*dest++ = val;
	return original_dest;
}
