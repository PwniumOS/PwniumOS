#ifndef _IO_PWN
#define _IO_PWN

#include <types.h>

static inline void outb(uint16_t port, uint8_t value)
{
    __asm__ __volatile__("outb %0, %1" : : "dN" (port), "a" (value));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ __volatile__("inb %0, %1" : "=a" (ret) : "dN" (port));
    return ret;
}

static inline uint16_t inw(uint16_t port)
{
    uint16_t ret;
    __asm__ __volatile__("inw %0, %1" : "=a" (ret) : "dN" (port));
    return ret;
}

#endif
