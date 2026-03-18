#include <stdlib.h>
#include <stdbool.h>

#define PS2_BASE 0xFF200100

volatile int pixel_buffer_start;	
volatile int * pixel_ctrl_ptr = (int *) 0xFF203020;	
short int Buffer1[240][512];	
short int Buffer2[240][512];	

struct box {
    short color;
    int x, y, dx, dy;
    int oldx1, oldy1, oldx2, oldy2;
};

void wait_for_vsync() {
    *pixel_ctrl_ptr = 1;	
    while ((*(pixel_ctrl_ptr + 3) & 0x00000001) != 0) {	
        continue;	
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
    struct box character;
    character.x = 100;
    character.y = 100;
    character.oldx1 = 100;
    character.oldy1 = 100;

    /* set front pixel buffer to Buffer 1 */
    *(pixel_ctrl_ptr + 1) = (int) &Buffer1; // set buffer1 as the back buffer first
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();	// swap buffers so buffer1 becomes front buffer
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;	// save the address of the current front buffer
    clear_screen(); // clear buffer1 to black

    /* set back pixel buffer to Buffer 2 */
    *(pixel_ctrl_ptr + 1) = (int) &Buffer2;	// set buffer2 as the back buffer
    pixel_buffer_start = *(pixel_ctrl_ptr + 1);	// point drawing to buffer2
    clear_screen();	// clear buffer2 to black
	//both buffers are black
	
    while (1)
    {
        for (int i = 0; i < 8; i++) {
			// erase the old line by using older previous position and filling it black
            draw_box(boxes[i].oldx2, boxes[i].oldy2, 0x0000);
        }

        for (int i = 0; i < 8; i++) {
            if (i != 7) {
				// erase the old line from this box to the next box
                draw_line(boxes[i].oldx2, boxes[i].oldy2, boxes[i+1].oldx2, boxes[i+1].oldy2, 0x0000);
            } else {
				// for the last box erase the line connecting it back to the first box
                draw_line(boxes[i].oldx2, boxes[i].oldy2, boxes[0].oldx2, boxes[0].oldy2, 0x0000);
            }
        }

		// determine direction box should move
        for (int i = 0; i < 8; i++) {
            if (boxes[i].x == 318) {	// if hit right edge move left
                boxes[i].dx = -1;
            } if (boxes[i].x == 1) {	// if hit left edge move right
                boxes[i].dx = 1;
            } if (boxes[i].y == 238) {	// if hit bottom edge move up
                boxes[i].dy = -1;
            } if (boxes[i].y == 1) {	// if hit top edge move down
                boxes[i].dy = 1;
            }
            boxes[i].x = boxes[i].x + boxes[i].dx;	// update x position
            boxes[i].y = boxes[i].y + boxes[i].dy;	// update y position
        }

        for (int i = 0; i < 8; i++) {
			// draw new box at its updated position
            draw_box(boxes[i].x, boxes[i].y, boxes[i].color);
            if (i != 7) {
				// draw line from first box to next box
                draw_line(boxes[i].x, boxes[i].y, boxes[i+1].x, boxes[i+1].y, boxes[i].color);
            } else {
				// last box connects back to the frist box
                draw_line(boxes[i].x, boxes[i].y, boxes[0].x, boxes[0].y, boxes[i].color);
            }
        }

        for (int i = 0; i < 8; i++) {
            boxes[i].oldx2 = boxes[i].oldx1;	// shift previous position history bakc one step
            boxes[i].oldy2 = boxes[i].oldy1;	// shift previous position history back one step
            boxes[i].oldx1 = boxes[i].x;	// save current x as most recent old x
            boxes[i].oldy1 = boxes[i].y;	// save current y as most recent old y
        }

        wait_for_vsync(); // wait for ertical sync and swap front/back buffers
        pixel_buffer_start = *(pixel_ctrl_ptr + 1);	// update pointer so drawing happens on new back buffer
    }
}

void plot_pixel(int x, int y, short int line_color)
{
    volatile short int *one_pixel_address;	// pointer to the memory address of one pixel
    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);	// calculate the pixel's memory location using x and y coordinates
    *one_pixel_address = line_color;	// write the color value to that pixel
}

void draw_box(int x, int y, short int color) {
	// loop between the x and y offset and fill in the color for each pixel
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            plot_pixel(x + i, y + j, color);
        }
    }
} 