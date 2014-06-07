#ifndef _IDT_PWN
#define _IDT_PWN

#include <types.h>

#define IDT_PRESENT 128
#define IDT_STORAGE 16
#define IDT_RING0 0
#define IDT_RING1 32
#define IDT_RING2 64
#define IDT_RING3 96
#define IDT_INTERRUPT_GATE 14
#define IDT_TRAP_GATE 15

#define DIVIDE_ERROR
#define DEBUG_EXCEPTION
#define INTEL_RESERVED
#define BREAKPOINT
#define OVERFLOW
#define BOUNDS_CHECK
#define INVALID_OPCODE
#define COPROCESSOR_NOT_AVAILABLE
#define DOUBLE_FAULT
#define COPROCESSOR_SEGMENT_OVERRUN
#define INVALID_TSS
#define SEGMENT_NOT_PRESENT
#define STACK_EXCEPTION
#define GP_EXCEPTION
#define PAGE_FAULT
#define INTEL_RESERVED
#define COPROCESSOR_ERROR

typedef void (*isr_handler)(struct isr_state *);

/*
flags:
      7                           0
    +---+---+---+---+---+---+---+---+
    | P |  DPL  | S |    GateType   |
    +---+---+---+---+---+---+---+---+

    P: Present ?
    DPL: Descriptor Privilege Level
    S: Storage
    GateType:
        - 0 D 1 1 0 = Interrupt Gate
        - 0 D 1 1 1 = Trap Gate
        D: size of gate (1=32bits, 0=16bits)
*/
struct idt_entry
{
    uint16_t base_lower;
    uint16_t seg_selector;
    uint8_t reserved;
    uint8_t flags;
    uint16_t base_upper;
} __attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));


struct isr_state
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags;
    unsigned int useresp, ss; // thos are valid only if a task switch occurs
};


void idt_init();
void interrupt_handler(struct isr_state *);

static inline void interrupt_disable() {
    __asm__ __volatile__("cli");
}

static inline void interrupt_enable() {
    __asm__ __volatile__("sti");
}

extern void idt_load();
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

#endif
