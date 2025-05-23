#include <io.h>
#include <multiboot.h>
#include <string.h>
#include <system.h>
#include <vga.h>

/* This is a very simple main() function. All it does is sit in an
 *  infinite loop. This will be like our 'idle' loop */
void kernel(uint32_t magic, multiboot_info_t* mbd)
{
	// VGA init and screen test
	init_video();
ciao mi chiamo filippo e

	if (!(mbd->flags >> 6 & 0x1))
	{
		kprintf("invalid memory map given by GRUB bootloader");
	}

	/* Loop through the memory map and display the values */
	size_t i;
	for (i = 0; i < mbd->mmap_length;)
	{
		multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*)(mbd->mmap_addr + i);

		kprintf("Start Addr: %X | Length: %X | Size: %x | Type: %d\n", mmmt->addr, mmmt->len, mmmt->size,
			mmmt->type);

		if (mmmt->type == MULTIBOOT_MEMORY_AVAILABLE)
		{
			/*
			 * Do something with this memory block!
			 * BE WARNED that some of memory shown as availiable is actually
			 * actively being used by the kernel! You'll need to take that
			 * into account before writing to memory!
			 */
		}

		i += mmmt->size + sizeof(mmmt->size);
	}

	bootinfo_stats(mbd);

	if (mbd->flags & (1 << 9))
	{
		kprintf("Booting with %s\tMAGIC: %x", mbd->boot_loader_name, magic);
	}

	/* ...and leave this loop in. There is an endless loop in
	 *  'start.asm' also, if you accidentally delete this next line */
	for (;;)
	{
		__asm__ __volatile__("hlt");
	}
}
