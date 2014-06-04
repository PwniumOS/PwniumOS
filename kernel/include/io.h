#ifndef IO_PWN
#define IO_PWN
#include <types.h>

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);

void outb(uint16_t port, uint8_t value)
{
    __asm__("outb %0, %1" : : "dN" (port), "a" (value));
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__("inb %0, %1" : "=a" (ret) : "dN" (port));
    return ret;
}

uint16_t inw(uint16_t port)
{
    uint16_t ret;
    __asm__("inw %0, %1" : "=a" (ret) : "dN" (port));
    return ret;
}

#endif
