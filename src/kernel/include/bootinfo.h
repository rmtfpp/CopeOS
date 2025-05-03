#ifndef __BOOTINFO_H
#define __BOOTINFO_H

#include "string.h"
#include "system.h"
#include "vga.h"

typedef struct __attribute__((packed))
{
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;

	// other stuff

} bootinfo_t;

void bootinfo_stats(bootinfo_t* bootinfo);

#endif
