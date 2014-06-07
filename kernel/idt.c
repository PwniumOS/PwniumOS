#include <idt.h>
#include <monitor.h>
#include <vga.h>
#include <printf.h>

#define IDT_COUNT 50

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

isr_handler exception_routines[] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

void interrupt_handler(struct isr_state *r) {
    isr_handler handler;

    printf("INTERRUPT %d: %s\n", r->int_no, exception_names[r->int_no]);

    handler = exception_routines[r->int_no];
    if (handler) {
        handler(r);
    }
    else {
        panic("No handler for interrupt %d: %s\n", r->int_no, exception_names[r->int_no]);
    }
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

    /* 32 Intel's defined Exceptions */
    idt_set_gate( 0, (uint32_t)isr0,  0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate( 1, (uint32_t)isr1,  0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate( 2, (uint32_t)isr2,  0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate( 3, (uint32_t)isr3,  0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate( 4, (uint32_t)isr4,  0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate( 5, (uint32_t)isr5,  0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate( 6, (uint32_t)isr6,  0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate( 7, (uint32_t)isr7,  0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate( 8, (uint32_t)isr8,  0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate( 9, (uint32_t)isr9,  0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(10, (uint32_t)isr10, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(11, (uint32_t)isr11, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(12, (uint32_t)isr12, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(13, (uint32_t)isr13, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(14, (uint32_t)isr14, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(15, (uint32_t)isr15, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(16, (uint32_t)isr16, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(17, (uint32_t)isr17, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(18, (uint32_t)isr18, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(19, (uint32_t)isr19, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(20, (uint32_t)isr20, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(21, (uint32_t)isr21, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(22, (uint32_t)isr22, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(23, (uint32_t)isr23, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(24, (uint32_t)isr24, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(25, (uint32_t)isr25, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(26, (uint32_t)isr26, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(27, (uint32_t)isr27, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(28, (uint32_t)isr28, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(29, (uint32_t)isr29, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(30, (uint32_t)isr30, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
    idt_set_gate(31, (uint32_t)isr31, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);

    idt_load();
}
