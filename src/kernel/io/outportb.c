#include <io.h>

// send a byte of data to the specified port
void outportb(uint16_t _port, uint8_t _data)
{
	__asm__ __volatile__("outb %1, %0" : : "dN"(_port), "a"(_data));
}
