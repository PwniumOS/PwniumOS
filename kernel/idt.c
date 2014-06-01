#include <idt.h>
#include <printf.h>

#define IDT_COUNT 2

struct idt_entry idt[IDT_COUNT];
struct idt_ptr idt_p;

char *exception_names[] = {
            "Divide Error",
            "Debug Exceptions",
            "Intel reserved",
            "Breakpoint",
            "Overflow",
            "Bounds Check",
            "Invalid Opcode",
            "Coprocessor Not Available",
            "Double Fault",
            "Coprocessor Segment Overrun",
            "Invalid TSS",
            "Segment Not Present",
            "Stack Exception",
            "General Protection Exception(Triple Fault)",
            "Page Fault",
            "Intel reserved",
            "Coprocessor Error"
};

void interrupt_handler(struct regs *r)
{
    printf("INTERRUPT %d: %s\n", r->int_no, exception_names[r->int_no]);
    for (;;);
}

void idt_set_gate(uint8_t num, uint32_t handler, uint16_t seg_selector, uint8_t flags) {
    idt[num].base_lower = handler & 0xFFFF;
    idt[num].base_upper = handler >> 16;
    idt[num].seg_selector = seg_selector;
    idt[num].flags = flags;
}

void idt_init() {
    idt_p.base = &idt;
    idt_p.limit = (sizeof(struct idt_entry) * IDT_COUNT - 1);


    idt_set_gate(0, (uint32_t)isr0, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(1, (uint32_t)isr1, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);

    idt_load();
}
