#include <gdt.h>

#define GPT_COUNT 3

struct gdt_entry gdt[GPT_COUNT];
struct gdt_ptr gp;

/* Setup a descriptor in the Global Descriptor Table */
void gdt_set_gate(int num, unsigned long base, unsigned long limit, uint8_t access, uint8_t gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void gdt_init()
{
    uint8_t access = 0, gran = 0;
    gp.limit = (sizeof(struct gdt_entry) * GPT_COUNT) - 1;
    gp.base = &gdt;

    gdt_set_gate(0, 0, 0, 0, 0);
    /*
        Code segment:
            access: 1 00 1 1 0 1 0 = 0x9A
            (PRESENT, RING 0, SYSTEM, EX, DC, Read/Write, Access)
            gran: 1100 XXXX
            (page granularity, 32bit protected mode)
    */
    access  = GDT_PRESENT | GDT_RING0 | GDT_NOT_SYSTEM | GDT_EXECUTABLE | GDT_RW;
    gran = GDT_PAGE_GRANULARITY | GDT_32BIT;
    gdt_set_gate(1, 0, 0xFFFFFFFF, access, gran);
    /*
        Data segment:
            access: 1 00 1 0 0 1 0 = 0x92
            (PRESENT, RING 0, SYSTEM, Grow Up, Read Only, Access)
            gran: 1100 XXXX
            (page granularity, 32bit protected mode)
    */

    access  = GDT_PRESENT | GDT_RING0 | GDT_NOT_SYSTEM | GDT_RW;
    gdt_set_gate(2, 0, 0xFFFFFFFF, access, gran);
    gdt_load();
}
