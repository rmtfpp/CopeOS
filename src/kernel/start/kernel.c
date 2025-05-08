#include <bootinfo.h>
#include <io.h>
#include <string.h>
#include <system.h>
#include <vga.h>

/* This is a very simple main() function. All it does is sit in an
 *  infinite loop. This will be like our 'idle' loop */
void kernel(uint32_t multiboot_magic, bootinfo_t* bootinfo)
{	
	// VGA init and screen test
	init_video();

	if(bootinfo->flags & (1 << 9))
	{
		uint8_t* name = (uint8_t*)(uintptr_t)(bootinfo->boot_loader_name);
		puts((uint8_t*)"Booting with ");
		puts(name);
		puts((uint8_t*) "\n");
	}	

	bootinfo_stats(bootinfo);
	puti(multiboot_magic);
	puts((uint8_t*)"\n");

		
	/* ...and leave this loop in. There is an endless loop in
	 *  'start.asm' also, if you accidentally delete this next line */
	for (;;)}
	{
		__asm__ __volatile__("hlt");
	}
}

// it is using 100% cpu wtf...
