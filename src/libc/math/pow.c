#include <math.h>

int32_t pow(int32_t base, size_t exp)
{
	int32_t res = 1;
	for (size_t i = 0; i < exp; i++)
	{
		res *= base;
	}
	return res;
}
