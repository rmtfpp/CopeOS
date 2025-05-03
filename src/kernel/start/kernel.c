#include <bootinfo.h>
#include <io.h>
#include <string.h>
#include <system.h>
#include <vga.h>

/* This is a very simple main() function. All it does is sit in an
 *  infinite loop. This will be like our 'idle' loop */
void kernel(uint32_t flags, uint32_t mem_lower, uint32_t mem_upper)
{
	// multiboot parameters initialization
	bootinfo_t multiboot_params = {flags, mem_lower, mem_upper};
	
	// VGA init and screen test
	init_video();
	bootinfo_stats(&multiboot_params);

	/* ...and leave this loop in. There is an endless loop in
	 *  'start.asm' also, if you accidentally delete this next line */
	for (;;)
		;
}
