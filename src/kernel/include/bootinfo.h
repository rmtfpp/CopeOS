#ifndef __BOOTINFO_H
#define __BOOTINFO_H

#include "string.h"
#include "system.h"
#include "vga.h"

typedef struct __attribute__((packed))
{
	uint32_t tabsize;
	uint32_t strsize;
	uint32_t addr;
	uint32_t reserved;
} multiboot_aout_symbol_table_t;

typedef struct __attribute__((packed))
{
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;
} multiboot_elf_section_header_table_t;

typedef struct __attribute__((packed))
{
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;

	uint32_t boot_device;
	uint32_t cmdline;
	uint32_t mods_count;
	uint32_t mods_addr;

	union {
		multiboot_aout_symbol_table_t	     aout_sym;
		multiboot_elf_section_header_table_t elf_sec;
	} syms;

	uint32_t mmap_length;
	uint32_t mmap_addr;
	uint32_t drives_length;
	uint32_t drives_addr;

	uint32_t config_table;

	uint32_t boot_loader_name;

	// other stuff

} bootinfo_t;

void bootinfo_stats(bootinfo_t* bootinfo);

#endif
