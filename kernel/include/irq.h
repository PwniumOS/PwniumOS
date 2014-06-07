#ifndef _IRQ_PWN
#define _IRQ_PWN

#define MASTER_COMMAND 0x20
#define MASTER_DATA 0x21
#define SLAVE_COMMAND 0xA0
#define SLAVE_DATA 0xA1
#define EOI 0x20
#define MASTER_ACK() outb(MASTER_COMMAND, EOI)
#define SLAVE_ACK() outb(SLAVE_COMMAND, EOI)

#define PIC_INIT 0x11

extern void irq0(void);
void irq_init();

#endif
