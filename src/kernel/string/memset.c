#include <string.h>

uint8_t* memset(uint8_t* dest, uint8_t val, size_t count)
{
	uint8_t* original_dest = dest;

	while (count != 0)
	{
		*dest = val;
		dest++;
		count--;
	}

	return original_dest;
}
