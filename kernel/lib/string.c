#include <string.h>

void *memset(void *mem, int c, size_t n)
{
    char *tmp = mem;
    for(size_t i = 0; i < n; i++) {
        tmp[i] = c;
    }
    return mem;
}

void *memcpy(void *dst, const void *src, size_t n)
{
    char *tmp = dst;
	const char *s = src;
    for(size_t i = 0; i < n; i++) {
        tmp[i] = s[i];
    }
    return dst;
}

size_t strlen(char *mem)
{
    size_t i = 0;
    while (*mem++) {
        i++;
    }
    return i;
}
