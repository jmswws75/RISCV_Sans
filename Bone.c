#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

int pixel_buffer_start; // global variable

void plot_pixel(int x, int y, short int line_color)
{
    volatile short int *one_pixel_address;
        one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
        *one_pixel_address = line_color;
}

// this function draws a vertical bone on the screen, at the specified coordinate.
// the coordinate starts at the top left, then goes down and right.
// for every bone, there are 3 parts: the top, bottom, and middle. the top and the bottom represents the "joint" of the bone, while the middle part is the flat part.
// the length in the function represents how long the middle part is. the smallest length is 1. inputting anything smaller than a 1 as length will result in a bone of length 1.
void draw_bone(int x0, int y0, int length, short int color) {
    draw_rectangle(x0, y0, x0+1, y0+2, color);
    draw_rectangle(x0+3, y0, x0+4, y0+2, color);
    draw_rectangle(x0, y0+2+length+1, x0+1, y0+4+length+1, color);
    draw_rectangle(x0+3, y0+2+length+1, x0+4, y0+4+length+1, color);

    // draw the middle part
    draw_rectangle(x0+1, y0+1, x0+3, y0+2+length+2, color);
}

void draw_line(int x0, int y0, int x1, int y1, int color){
	bool is_steep = abs(y1 - y0) > abs(x1 - x0);
    if (is_steep) {
        int temp = x0;
        x0 = y0;
        y0 = temp;
        temp = x1;
        x1 = y1;
        y1 = temp;
    }
    if (x0 > x1) {
        int temp = x0;
        x0 = x1;
        x1 = temp;
        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    int dx = x1 - x0;
    int dy = abs(y1 - y0);
    int error = -(dx / 2);
    int y = y0;
    int y_step;
    if (y0 < y1) {y_step = 1;} else {y_step = -1;}

    for (int x = x0; x <= x1; x++) {
        if (is_steep) {
            plot_pixel(y, x, color);
        } else {
            plot_pixel(x, y, color);
        }
        error = error + dy;
        if (error > 0) {
            y = y + y_step;
            error = error - dx;
        }
    }
}

// this function draws a rectangle (filled) on the screen with the correct color.
// point 0 must be on the top left, 1 must be on bottom right, else the code does not work
// I am too lazy to write the swap logic to figure out the order of traversal.
void draw_rectangle(int x0, int y0, int x1, int y1, short int color) {
    
    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            plot_pixel(i, j, color);
        }
    }
}

void clear_screen(){
    for (int i = 0; i < 320; i++) {
        for (int j = 0; j < 240; j++) {
            plot_pixel(i, j, 0x0000);
        }
    }
}

int main(void)
{
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;

    int curry = 0;
    int dy = -1;

    clear_screen();
    draw_rectangle(120, 113, 202, 115, 0xFFFF);
    draw_rectangle(120, 113, 122, 195, 0xFFFF);
    draw_rectangle(120, 193, 202, 195, 0xFFFF);
    draw_rectangle(200, 113, 202, 195, 0xFFFF);

    for (int i = 0; i < 200; i+=6) {
        draw_bone(1+i,1,10 + i/3, 0xFFFF);
    }

    while (1) {
        if ((*(pixel_ctrl_ptr + 3) & 0x00000001) != 0) {
            continue;
        }
        
        // if(curry == 239) {
        //     dy = -1;
        // } else if (curry == 0) {
        //     dy = 1;
        // }

        // draw_line(0, curry, 319, curry, 0x0000);
        // curry = curry + dy;
        // draw_line(0, curry, 319, curry, 0xFFFF);

        *pixel_ctrl_ptr = 1;

    }
    
}
