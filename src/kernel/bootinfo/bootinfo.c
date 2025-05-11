#include <multiboot.h>

void bootinfo_stats(multiboot_info_t* bootinfo)
{
	kprintf("flags: %d\tmmap_length: %d\tmmap_addr: %d\n", bootinfo->flags, bootinfo->mmap_length,
		bootinfo->mmap_addr);
}
