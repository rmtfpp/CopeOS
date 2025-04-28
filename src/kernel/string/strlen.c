#include <string.h>

size_t strlen(const uint8_t* str)
{
	size_t len = 0;
	for (; *str != 0; str++)
	{
		len++;
	}
	return len;
}
