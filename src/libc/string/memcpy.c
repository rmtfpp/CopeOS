#include <string.h>

void* memcpy(void* to, const void* from, size_t count)
{
	uint8_t*       dest = to;
	const uint8_t* src  = from;

	while (count != 0)
	{
		*dest = *src;
		dest++;
		src++;
		count--;
	}

	return to;
}
