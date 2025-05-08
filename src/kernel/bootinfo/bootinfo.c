#include <bootinfo.h>

void bootinfo_stats(bootinfo_t* bootinfo)
{
	puts("flags: ");
	puti(bootinfo->flags);
	puts((uint8_t*)"\n");

	puts("mem_lower: ");
	puti(bootinfo->mem_lower);
	puts((uint8_t*)"\n");

	puts("mem_upper: ");
	puti(bootinfo->mem_upper);
	puts((uint8_t*)"\n");
}
