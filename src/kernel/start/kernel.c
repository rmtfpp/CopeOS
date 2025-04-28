#include <io.h>
#include <string.h>
#include <vga.h>
#include <system.h>

/* This is a very simple main() function. All it does is sit in an
 *  infinite loop. This will be like our 'idle' loop */
void kernel()
{
	// VGA init and screen test 

	uint8_t* literal = (uint8_t*) "Hello, kernel world!\n";
	init_video();
	puts(literal);
	/* You would add commands after here */

	/* ...and leave this loop in. There is an endless loop in
	 *  'start.asm' also, if you accidentally delete this next line */
	for (;;)
		;
}
