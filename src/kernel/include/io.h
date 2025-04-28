#ifndef __IO_H
#define __IO_H

#include "system.h"

extern uint8_t inportb(uint16_t _port);
extern void    outportb(uint16_t _port, uint8_t _data);

#endif
