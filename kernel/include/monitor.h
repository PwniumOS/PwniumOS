#ifndef MONITOR_PWN
#define MONITOR_PWN
#include <types.h>

void monitor_clear();

void monitor_put_char(char c);

void monitor_put_string(char *c);
void monitor_put_char_at(uint8 x, uint8 y, char c);

#endif
