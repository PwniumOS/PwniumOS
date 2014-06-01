#ifndef _GDT_H
#define _GDT_H

#include <types.h>

#define GDT_PRESENT 128
#define GDT_RING3 96
#define GDT_RING2 64
#define GDT_RING1 32
#define GDT_NOT_SYSTEM 16
#define GDT_EXECUTABLE 8
#define GDT_GROW_UP 4
#define GDT_CONFORMING 4
#define GDT_RW 2
#define GDT_ACCESS 1
#define GDT_RING0 0

#define GDT_PAGE_GRANULARITY 128
#define GDT_32BIT 64
#define GDT_16BIT 0


struct gdt_entry
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity; //  flags(4 bits) + limit 16-> 19
	uint8_t base_high;
} __attribute__((packed));


struct gdt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

extern void gdt_load(); // in boot.asm
void gdt_init();

#endif
