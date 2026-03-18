#include <stdlib.h>
#include <stdbool.h>

#define PS2_BASE 0xFF200100

volatile int pixel_buffer_start;
volatile int *pixel_ctrl_ptr = (int *)0xFF203020;
volatile int *PS2_ptr = (int *)PS2_BASE;

short int Buffer1[240][512];
short int Buffer2[240][512];

struct box {
    short color;
    int x, y;
    int oldx1, oldy1;
};

void plot_pixel(int x, int y, short int color);
void draw_box(int x, int y, short int color);
void clear_screen(void);
void wait_for_vsync(void);

void wait_for_vsync(void) {
    *pixel_ctrl_ptr = 1;
    while ((*(pixel_ctrl_ptr + 3) & 0x00000001) != 0) {
    }
}
void clear_screen(void) {
    int i, j;
    for (i = 0; i < 320; i++) {
        for (j = 0; j < 240; j++) {
            plot_pixel(i, j, 0x0000);
        }
    }
}

int main(void) {
    struct box character;

    int PS2_data;
    int RVALID;
    char byte;

    character.x = 100;
    character.y = 100;
    character.oldx1 = 100;
    character.oldy1 = 100;
    character.color = 0xFFFF;

    *(pixel_ctrl_ptr + 1) = (int)&Buffer1;
    wait_for_vsync();
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen();

    *(pixel_ctrl_ptr + 1) = (int)&Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);
    clear_screen();

    draw_box(character.x, character.y, character.color);

    while (1) {
        character.oldx1 = character.x;
        character.oldy1 = character.y;

        PS2_data = *PS2_ptr;
        RVALID = PS2_data & 0x8000;

        if (RVALID) {
            byte = PS2_data & 0xFF;

            if (byte == 0x1D) {          // W
                if (character.y > 0) {
                    character.y--;
                }
            }
            else if (byte == 0x1C) {     // A
                if (character.x > 0) {
                    character.x--;
                }
            }
            else if (byte == 0x1B) {     // S
                if (character.y < 238) {
                    character.y++;
                }
            }
            else if (byte == 0x23) {     // D
                if (character.x < 318) {
                    character.x++;
                }
            }
        }

        draw_box(character.oldx1, character.oldy1, 0x0000);
        draw_box(character.x, character.y, character.color);

        wait_for_vsync();
        pixel_buffer_start = *(pixel_ctrl_ptr + 1);
    }
}

void plot_pixel(int x, int y, short int color) {
    volatile short int *one_pixel_address;
    one_pixel_address = (volatile short int *)(pixel_buffer_start + (y << 10) + (x << 1));
    *one_pixel_address = color;
}

void draw_box(int x, int y, short int color) {
    plot_pixel(x, y, color);
    plot_pixel(x + 1, y, color);
    plot_pixel(x, y + 1, color);
    plot_pixel(x + 1, y + 1, color);
}