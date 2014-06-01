#ifndef _MONITOR_H
#define _MONITOR_H
#include <types.h>

void monitor_clear();

void monitor_put_char(char c);

void monitor_put_string(char *c);
void monitor_put_char_at(uint8_t x, uint8_t y, char c);

#endif
