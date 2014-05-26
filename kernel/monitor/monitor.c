#include <monitor.h>
#include <asm/io.h>

uint16 *video_memory = (uint16 *)0xB8000;
uint8 cursor_x = 0;
uint8 cursor_y = 0;

static void move_cursor()
{
    uint16 cursorLocation = cursor_y * 80 + cursor_x;
    outb(0x3D4, 14);                  // high cursor byte.
    outb(0x3D5, cursorLocation >> 8); // Send!
    outb(0x3D4, 15);                  // low cursor byte.
    outb(0x3D5, cursorLocation);      // Send!
}

void monitor_clear()
{
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

void monitor_put_char_at(uint8 x, uint8 y, char c)
{
    uint16 pos = y * 80 + x;
    uint8 color = (0 << 4) | (15 & 0x0F);
    video_memory[pos] = (color << 8) + c;
}

void monitor_put_char(char c)
{
    monitor_put_char_at(cursor_x, cursor_y, c);
    cursor_x++;
    if (cursor_x >= 80) {
        cursor_y++;
        cursor_x = 0;
    }
    move_cursor();
}

void monitor_put_string(char *c)
{
    while (*c) {
        monitor_put_char(*c++);
    }
}
