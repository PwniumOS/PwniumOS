#ifndef MONITOR_PWN
#define MONITOR_PWN
#include <types.h>

void monitor_clear();

void monitor_put_char(char c);

void monitor_put_string(char *c);
void monitor_put_char_at(uint8_t x, uint8_t y, char c);

void itoa (char *buf, int base, int d);
void mprintf (const char *format, ...);

#endif
