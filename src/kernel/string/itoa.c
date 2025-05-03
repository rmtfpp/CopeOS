#include <string.h>

uint8_t* itoa(int32_t number, uint8_t* arr, size_t base)
{
	bool   negative = false;
	size_t i	= 0;
	size_t r;

	if (number == 0)
	{
		arr[i]	   = '0';
		arr[i + 1] = '\0';
		return arr;
	}

	if (number < 0 && base == 10)
	{
		number *= -1;
		negative = 1;
	}

	while (number != 0)
	{
		r      = number % base;
		arr[i] = (r > 9) ? (r - 10) + 'a' : r + '0';
		i++;
		number /= base;
	}

	if (negative)
	{
		arr[i] = '-';
		i++;
	}

	strrev(arr, 0, i - 1);

	arr[i] = '\0';

	return arr;
}
