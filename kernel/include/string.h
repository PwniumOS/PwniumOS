#ifndef _STRING_H
#define _STRING_H

#include <types.h>

void *memset(void *mem, int c, size_t n);
void *memcpy(void *dst, const void *src, size_t n);
size_t strlen(char *mem);


#endif
