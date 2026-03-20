#include <stdbool.h>
#include <stdlib.h>

#define PS2_BASE 0xFF200100

volatile int pixel_buffer_start;
volatile int *pixel_ctrl_ptr = (int *)0xFF203020;
volatile int *PS2_ptr = (int *)PS2_BASE;

void plot_pixel(int x, int y, short int color);
void clear_screen(void);
void draw_rectangle(int x0, int y0, int x1, int y1, short int color);
void draw_player(int x, int y, short int color);

void plot_pixel(int x, int y, short int color)
{
    volatile short int *one_pixel_address;
    one_pixel_address = (volatile short int *)(pixel_buffer_start + (y << 10) + (x << 1));
    *one_pixel_address = color;
}

void clear_screen(void)
{
    int x, y;
    for (x = 0; x < 320; x++) {
        for (y = 0; y < 240; y++) {
            plot_pixel(x, y, 0x0000);
        }
    }
}

void draw_rectangle(int x0, int y0, int x1, int y1, short int color)
{
    int x, y;
    for (x = x0; x <= x1; x++) {
        for (y = y0; y <= y1; y++) {
            plot_pixel(x, y, color);
        }
    }
}

void draw_player(int x, int y, short int color)
{
    draw_rectangle(x, y, x + 1, y + 1, color);
}

int main(void)
{
    int x = 10;
    int y = 120;
    int old_x = x;
    int old_y = y;

    int PS2_data;
    int RVALID;
    char byte;
    char last_byte = 0;

    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();
    draw_player(x, y, 0xFFFF);

    while (1) {
        old_x = x;
        old_y = y;

        while (1) {
            PS2_data = *PS2_ptr;
            RVALID = PS2_data & 0x8000;
            if (!RVALID){
                break;
			}

            byte = PS2_data & 0xFF;

            if (byte != (char)0xF0 && last_byte != (char)0xF0) {
                if (byte == (char)0x1D) {
                    if (y > 0) y--;
                }
                else if (byte == (char)0x1C) {
                    if (x > 0) x--;
                }
                else if (byte == (char)0x1B) {
                    if (y < 238) y++;
                }
                else if (byte == (char)0x23) {
                    if (x < 318) x++;
                }
            }

            last_byte = byte;
        }

        if (x != old_x || y != old_y) {
            draw_player(old_x, old_y, 0x0000);
            draw_player(x, y, 0xFFFF);
        }
    }

    return 0;
}