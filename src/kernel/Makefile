.PHONY: build-bin, build-iso, run, clean

COMPILER = i686-elf-gcc
ASSEMBLER = nasm
LINKER = i686-elf-ld

CFLAGS = -c -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I./include/ -nostdlib
SFLAGS = -felf32
LDFLAGS = -nostdlib

LINKFILE = linker.ld

ROOT = ../../
TARGET = ../../target
BINARY = $(TARGET)/boot/CopeOS.bin
ISO = $(ROOT)/iso/CopeOS.iso

C_SOURCES := $(shell find . -name '*.c')
S_SOURCES := $(shell find . -name '*.s')
C_OBJS := $(C_SOURCES:.c=.o)
S_OBJS := $(S_SOURCES:.s=.o)

%.o: %.c
	$(COMPILER) $(CFLAGS) $< -o $@

%.o: %.s
	$(ASSEMBLER) $(SFLAGS) $< -o $@

$(BINARY): $(LINKFILE) $(C_OBJS) $(S_OBJS)
	mkdir -p $(TARGET)/boot/
	$(LINKER) -T $(LINKFILE) -o $(BINARY) $(C_OBJS) $(S_OBJS)

build-bin: $(BINARY)
	@echo "BINARY FILE BUILT"

$(ISO): $(BINARY)
	grub2-file --is-x86-multiboot $(BINARY)
	grub2-mkrescue -o $(ISO) $(TARGET)

build-iso: $(ISO)
	@echo "ISO IMAGE BUILT"

run: $(ISO) 
	qemu-system-i386 -cdrom $(ISO)

clean:
	find . -name '*.o' -delete
