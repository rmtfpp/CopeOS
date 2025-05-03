#include <string.h>

void strrev(uint8_t* arr, int32_t start, int32_t end)
{
	uint8_t temp;

	if (start >= end)
		return;

	temp	       = *(arr + start);
	*(arr + start) = *(arr + end);
	*(arr + end)   = temp;

	start++;
	end--;
	strrev(arr, start, end);
}
