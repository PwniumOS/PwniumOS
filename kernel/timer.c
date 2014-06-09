#include <io.h>

uint32_t tick = 0;

void timer_tick(struct isr_state *r) {
    printf("%d Tick..\n", tick++);
}

void timer_init() {
    irq_install_handler(0, timer_tick);
}
