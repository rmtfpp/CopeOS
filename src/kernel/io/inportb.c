#include <io.h>

/* We will use this later on for reading from the I/O ports to get data
 *  from devices such as the keyboard. We are using what is called
 *  'inline assembly' in these routines to actually do the work */
uint8_t inportb(unsigned short _port)
{
	unsigned char rv;
	__asm__ __volatile__("inb %1, %0" : "=a"(rv) : "dN"(_port));
	return rv;
}
