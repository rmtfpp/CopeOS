#ifndef __IO_H
#define __IO_H

#include "system.h"

extern unsigned char inportb(unsigned short _port);
extern void	     outportb(unsigned short _port, unsigned char _data);

#endif
