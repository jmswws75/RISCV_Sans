#include <stdbool.h>
#include <stdlib.h>

#define PS2_BASE 0xFF200100

int pixel_buffer_start;

void plot_pixel(int x, int y, short int color);
void draw_rectangle(int x0, int y0, int x1, int y1, short int color);
void draw_player(int x, int y, short int color);

void plot_pixel(int x, int y, short int color)
{
    volatile short int *one_pixel_address;
    one_pixel_address = (volatile short int *)(pixel_buffer_start + (y << 10) + (x << 1));
    *one_pixel_address = color;
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
    volatile int *pixel_ctrl_ptr = (int *)0xFF203020;
    volatile int *PS2_ptr = (int *)PS2_BASE;

    int x = 10;
    int y = 120;

    int PS2_data;
    int RVALID;
    char byte;

    pixel_buffer_start = *pixel_ctrl_ptr;

    draw_player(x, y, 0xFFFF);

    while (1) {
        PS2_data = *PS2_ptr;
        RVALID = PS2_data & 0x8000;

        if (RVALID) {
            byte = PS2_data & 0xFF;

            draw_player(x, y, 0x0000);

            if (byte == 0x1D) {          //W
                if (y > 0) {             //Second if statement contains the boundary condition for movement
                    y--;
                }
            }
            else if (byte == 0x1C) {     //A
                if (x > 0) {
                    x--;
                }
            }
            else if (byte == 0x1B) {     //S
                if (y < 238) {
                    y++;
                }
            }
            else if (byte == 0x23) {     //D
                if (x < 318) {
                    x++;
                }
            }

            draw_player(x, y, 0xFFFF);
        }
    }

    return 0;
}