#include <io.h>

void timer_tick(struct isr_state *r) {
    printf("Tick..\n");
}

void timer_init() {
    irq_install_handler(0, timer_tick);
}
