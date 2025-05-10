#include <multiboot.h>

void bootinfo_stats(multiboot_info_t* bootinfo)
{
	puts((uint8_t*)"flags: ");
	puti(bootinfo->flags);
	puts((uint8_t*)"\n");

	puts((uint8_t*)"mmap_length: ");
	puti(bootinfo->mmap_length);
	puts((uint8_t*)"\n");

	puts((uint8_t*)"mmap_addr: ");
	puti(bootinfo->mmap_addr);
	puts((uint8_t*)"\n");
}
