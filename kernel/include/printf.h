#ifndef _PRINTF_H
#define _PRINTF_H

#include <types.h>

int printf(const char *fmt, ...);
void panic(const char *fmt, ...);
int sprintf(char *buf, const char *fmt, ...);

#endif
