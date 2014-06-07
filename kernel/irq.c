#include <irq.h>
#include <types.h>
#include <io.h>
#include <idt.h>


static isr_handler irq_routines[16] = {
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};

/*
	By default IRQs 0 to 7 are mapped to idt's entries 8 to 15
	which they are used to handle interrupts
*/
static void irq_remap() {
	unsigned char mask1, mask2;

	mask1 = inb(MASTER_DATA);                        // save masks
	mask2 = inb(SLAVE_DATA);
	outb(MASTER_COMMAND, PIC_INIT);
    outb(SLAVE_COMMAND, PIC_INIT);
    outb(MASTER_DATA, 0x20);
    outb(SLAVE_DATA, 0x28);
    outb(MASTER_DATA, 0x04);
    outb(SLAVE_DATA, 0x02);
    outb(MASTER_DATA, 0x01);
    outb(SLAVE_DATA, 0x01);
    outb(MASTER_DATA, mask1); // keep only the timer
    outb(SLAVE_DATA, mask2); // mask all interrupt coming from the slave
}

void irq_install_handler(int irq, isr_handler handler) {
	irq_routines[irq] = handler;
}

void irq_handler(struct isr_state *r) {
	isr_handler handler;

	printf("IRQ %d\n", r->int_no);
	handler = irq_routines[r->int_no];
	if (handler) {
		handler(r);
	} else {
		printf("IRQ %d handler is not installed\n");
	}

	if (r->int_no >= 8) { // from the slave PIC
        SLAVE_ACK();
    }

    MASTER_ACK();
}

void irq_init() {
	irq_remap();
	/* for the time being only the timer is installed */
	for(size_t i = 0; i < 16; i++) {
		idt_set_gate(32 + i, (uint32_t)irq0, 0x8, IDT_PRESENT | IDT_RING0 | IDT_INTERRUPT_GATE);
	}
}
