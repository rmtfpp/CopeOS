#include <io.h>
#include <string.h>
#include <vga.h>

uint16_t* textmemptr;
size_t	  attrib = 0x0F;
size_t	  csr_x	 = 0;
size_t	  csr_y	 = 0;

void scroll(void)
{
	uint16_t blank;
	uint16_t temp;

	// white space (0x20 ASCII) on black background
	blank = 0x20 | (attrib << 8);

	if (csr_y >= 25)
	{
		// Move the current text chunk that makes up the screen
		//  back in the buffer by a line
		temp = csr_y - 25 + 1;
		memcpy(textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);

		// Finally, we set the chunk of memory that occupies
		//  the last line of text to our 'blank' character
		memsetw(textmemptr + (25 - temp) * 80, blank, 80);
		csr_y = 25 - 1;
	}
}

/* Updates the hardware cursor: the little blinking line
 *  on the screen under the last character pressed! */
void move_csr(void)
{
	uint16_t temp;

	/* The equation for finding the index in a linear
	 *  chunk of memory can be represented by:
	 *  Index = [(y * width) + x] */
	temp = csr_y * 80 + csr_x;

	/* This sends a command to indicies 14 and 15 in the
	 *  CRT Control Register of the VGA controller. These
	 *  are the high and low bytes of the index that show
	 *  where the hardware cursor is to be 'blinking'. To
	 *  learn more, you should look up some VGA specific
	 *  programming documents. A great start to graphics:
	 *  http://www.brackeen.com/home/vga */
	outportb(0x3D4, 14);
	outportb(0x3D5, temp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, temp);
}

/* Clears the screen */
void cls()
{
	uint16_t blank;
	int	 i;

	/* Again, we need the 'short' that will be used to
	 *  represent a space with color */
	blank = 0x20 | (attrib << 8);

	/* Sets the entire screen to spaces in our current
	 *  color */
	for (i = 0; i < 25; i++)
		memsetw(textmemptr + i * 80, blank, 80);

	/* Update out virtual cursor, and then move the
	 *  hardware cursor */
	csr_x = 0;
	csr_y = 0;
	move_csr();
}

/* Puts a single character on the screen */
void putc(uint8_t c)
{
	uint16_t* where;
	uint16_t  att = attrib << 8;

	/* Handle a backspace, by moving the cursor back one space */
	if (c == 0x08)
	{
		if (csr_x != 0)
			csr_x--;
	}
	/* Handles a tab by incrementing the cursor's x, but only
	 *  to a point that will make it divisible by 8 */
	else if (c == 0x09)
	{
		csr_x = (csr_x + 8) & ~(8 - 1);
	}
	/* Handles a 'Carriage Return', which simply brings the
	 *  cursor back to the margin */
	else if (c == '\r')
	{
		csr_x = 0;
	}
	/* We handle our newlines the way DOS and the BIOS do: we
	 *  treat it as if a 'CR' was also there, so we bring the
	 *  cursor to the margin and we increment the 'y' value */
	else if (c == '\n')
	{
		csr_x = 0;
		csr_y++;
	}
	/* Any character greater than and including a space, is a
	 *  printable character. The equation for finding the index
	 *  in a linear chunk of memory can be represented by:
	 *  Index = [(y * width) + x] */
	else if (c >= ' ')
	{
		where  = textmemptr + (csr_y * 80 + csr_x);
		*where = c | att; /* Character AND attributes: color */
		csr_x++;
	}

	/* If the cursor has reached the edge of the screen's width, we
	 *  insert a new line in there */
	if (csr_x >= 80)
	{
		csr_x = 0;
		csr_y++;
	}

	/* Scroll the screen if needed, and finally move the cursor */
	scroll();
	move_csr();
}

/* Uses the above routine to output a string... */
void puts(uint8_t* text)
{
	size_t i;

	for (i = 0; i < strlen(text); i++)
	{
		putc(text[i]);
	}
}

void puti(int32_t num)
{
	if (num < 0)
	{
		putc('-');
		num = -num;
	}

	size_t	num_digits = 1;
	int32_t temp	   = num;

	while (temp >= 10)
	{
		temp /= 10;
		num_digits++;
	}

	for (size_t i = num_digits; i > 0; i--)
	{
		int32_t divisor = pow(10, i - 1);
		int32_t digit	= num / divisor;
		putc((uint8_t)(digit + '0'));
		num %= divisor;
	}
}

void putx(uint32_t num)
{
	int started = 0; // Used to skip leading zeros
	for (int i = 28; i >= 0; i -= 4)
	{
		uint8_t nibble = (num >> i) & 0xF;
		if (nibble != 0 || started || i == 0)
		{
			started = 1;
			if (nibble < 10)
				putc('0' + nibble);
			else
				putc('A' + (nibble - 10));
		}
	}
}

/* Sets the forecolor and backcolor that we will use */
void settextcolor(uint8_t forecolor, uint8_t backcolor)
{
	/* Top 4 bytes are the background, bottom 4 bytes
	 *  are the foreground color */
	attrib = (backcolor << 4) | (forecolor & 0x0F);
}

void kprintf(const char* format_str, ...)
{
	uint8_t* format = (uint8_t*) format_str;
	uint8_t buffer[256];
	size_t	buffer_pos = 0;

	// parsing extra arguments that are on the stack
	// address of first argument after format
	void** args_ptr;
	__asm__ __volatile__("leal 8(%%ebp), %0" : "=r"(args_ptr));

	args_ptr++;

	for (size_t i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			// charachters before printing
			if (buffer_pos > 0)
			{
				buffer[buffer_pos] = '\0';
				puts(buffer);
				buffer_pos = 0;
			}

			// format specifier handler
			switch (format[++i])
			{
			case 's': {
				uint8_t* str = (uint8_t*)*args_ptr++;
				puts(str);
				break;
			}
			case 'd': {
				size_t value = (size_t)*args_ptr++;
				puti(value);
				break;
			}
			case 'x': {
				size_t value = (size_t)*args_ptr++;
				putx(value);
				break;
			}
			case 'c': {
				// char promoted to int for calling conventions
				char c = (uint8_t)(size_t)*args_ptr++;
				putc(c);
				break;
			}
			case '%': {
				putc('%');
				break;
			}
			default: {
				// in case format spec is not s d x c
				putc('%');
				putc(format[i]);
				break;
			}
			}
		}
		else
		{
			// put current char into the buffer
			buffer[buffer_pos++] = format[i];

			// clear the buffer
			if (buffer_pos >= 255)
			{
				buffer[buffer_pos] = '\0';
				puts(buffer);
				buffer_pos = 0;
			}
		}
	}

	// Output any remaining characters in the buffer
	if (buffer_pos > 0)
	{
		buffer[buffer_pos] = '\0';
		puts(buffer);
	}
}

/* Sets our text-mode VGA pointer, then clears the screen for us */
void init_video(void)
{
	textmemptr = (uint16_t*)0xB8000;
	cls();
}
