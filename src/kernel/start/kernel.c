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

	
	if (!(mbd->flags >> 6 & 0x1))
	{
		puts("invalid memory map given by GRUB bootloader");
	}

	/* Loop through the memory map and display the values */
	size_t i;
	for (i = 0; i < mbd->mmap_length; i += sizeof(multiboot_memory_map_t))
	{
		multiboot_memory_map_t* mmmt = (multiboot_memory_map_t*)(mbd->mmap_addr + i);
		
		puti(i);
		puts((uint8_t*) " | ");

		puts("Start Addr: ");
		putx(mmmt->addr);


		puts(" | Length: ");
		putx(mmmt->len);

		puts(" | Size: ");
		puti(mmmt->size);


		puts(" | Type: ");
		puti(mmmt->type);
		puts((uint8_t*)"\n");


		if (mmmt->type == MULTIBOOT_MEMORY_AVAILABLE)
		{
			/*
			 * Do something with this memory block!
			 * BE WARNED that some of memory shown as availiable is actually
			 * actively being used by the kernel! You'll need to take that
			 * into account before writing to memory!
			 */
		}
	}

	bootinfo_stats(mbd);
	puti(magic);
	puts((uint8_t*)"\n");

	if (mbd->flags & (1 << 9))
	{
		puts(mbd->boot_loader_name);
	}


	/* ...and leave this loop in. There is an endless loop in
	 *  'start.asm' also, if you accidentally delete this next line */
	for (;;)
	{
		__asm__ __volatile__("hlt");
	}
}
