#include <monitor.h>
#include <vga.h>
#include <asm/io.h>

uint16_t *video_memory = (uint16_t *)0xB8000;
uint8_t cursor_x = 0;
uint8_t cursor_y = 0;
uint8_t color = VGA_WHITE_ON_BLACK;

static void move_cursor() {
    uint16_t cursor_pos = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);              // high cursor byte.
    outb(0x3D5, cursor_pos >> 8); // Send!
    outb(0x3D4, 15);              // low cursor byte.
    outb(0x3D5, cursor_pos);      // Send!
}

void monitor_clear() {
    int i, j;
    for (i = 0; i < 80; i++) {
        for (j = 0; j < 25; ++j) {
        monitor_put_char_at(i, j, ' ');
        }
    }

    cursor_y = 0;
    cursor_x = 0;
    move_cursor();
}

void monitor_put_char_at(uint8_t x, uint8_t y, char c) {
    uint16_t pos = y * 80 + x;
    video_memory[pos] = (color << 8) + c;
}

uint8_t monitor_make_color(uint8_t fg, uint8_t bg) { return fg | bg << 4; }

inline void monitor_set_color(uint8_t c) { color = c; }

void monitor_put_char(char c) {

    if (c == '\n') {
        cursor_y++;
        cursor_x = 0;
    } else if (c == '\t') {
        cursor_x += 4;
    } else {
        monitor_put_char_at(cursor_x, cursor_y, c);
        cursor_x++;
    }
    
    if (cursor_x >= 80) {
        cursor_y++;
        cursor_x = 0;
    }
    move_cursor();
}

void monitor_put_string(char *c) {
    while (*c) {
        monitor_put_char(*c++);
    }
}

void itoa (char *buf, int base, int d)
{
    char *p = buf;
    char *p1, *p2;
    unsigned long ud = d;
    int divisor = 10;

    /* If %d is specified and D is minus, put `-' in the head. */
    if (base == 'd' && d < 0) {
        *p++ = '-';
        buf++;
        ud = -d;
    } else if (base == 'x' || base == 'p') // TODO: add 0x in case of %p
        divisor = 16;

    /* Divide UD by DIVISOR until UD == 0. */
    do {
        int remainder = ud % divisor;

        *p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
    } while (ud /= divisor);

    /* Terminate BUF. */
    *p = 0;

    /* Reverse BUF. */
    p1 = buf;
    p2 = p - 1;
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}

void mprintf (const char *format, ...)
{
    char **arg = (char **) &format;
    int c;
    char buf[20];

    arg++;

    while ((c = *format++) != 0) {
        if (c != '%')
            monitor_put_char(c);
        else {
            char *p;

            c = *format++;
            switch (c) {
            case 'd':
            case 'u':
            case 'x':
                itoa (buf, c, *((int *) arg++));
                p = buf;
                goto string;
                break;

            case 's':
                p = *arg++;
                if (! p)
                    p = "(null)";
string:
                while (*p)
                    monitor_put_char(*p++);
                break;

            default:
                monitor_put_char(*((int *) arg++));
                break;
            }
        }
    }
}
