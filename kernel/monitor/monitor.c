#include <monitor.h>
#include <vga.h>
#include <io.h>

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

uint8_t monitor_make_color(uint8_t fg, uint8_t bg) {
    return fg | bg << 4;
}

void monitor_set_color(uint8_t c) {
    color = c;
}

static void monitor_scroll(void)
{
    uint16_t blank = 0x20 | (color << 8);

    memcpy (video_memory, video_memory + 80, 24 * 80 * 2);
    /* delete last line */
    uint16_t pos = 24 * 80;
    for(size_t i = 0; i < 80; i++)
    {
        video_memory[pos + i] = blank;
    }
    cursor_y = 24;
}

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
    if (cursor_y > 24)
        monitor_scroll();
    move_cursor();
}

void monitor_put_string(char *c) {
    while (*c) {
        monitor_put_char(*c++);
    }
}
