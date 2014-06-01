#include <types.h>

#define IDT_PRESENT 128
#define IDT_STORAGE 16
#define IDT_RING0 0
#define IDT_RING1 32
#define IDT_RING2 64
#define IDT_RING3 96
#define IDT_INTERRUPT_GATE 14
#define IDT_TRAP_GATE 15

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

/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */
};


void idt_init();
void interrupt_handler(struct regs *r);
extern void idt_load();
extern void isr0();
extern void isr1();
