// --- Start of .\Test folder\graphics.h ---
#ifndef GRAPHICS_H
#define GRAPHICS_H

#define GASTER_BLASTER_HEIGHT 56
#define GASTER_BLASTER_WIDTH 22

struct Bone {
    // the positions and velocities are stored as multiples of 256 (2^8).
    // i.e. x = 256 means x = 1. same for velocities.
    // this is to make the calculation easier for the cpu. (avoid floating point arithmatic)
    int posx[3];
    int posy[3];
    int length;
    int velox;
    int veloy;
    short int color;
};

struct blaster {
    int posx;
    int posy;
    int centerx;
    int centery;
    int size;
    int rotation;
    // the blaster will stay on screen for 100 frames total.
    // it takes 20 + 48 frames to appear before firing. after it fires, it will stay there for 80 frames.
    int frameCount;
};

struct platform {

};

void wait_for_vsync();
void plot_pixel(int x, int y, short int line_color);
void update_pos(int newPos, int pos[]);
void draw_blaster();
void draw_bone(int x0, int y0, int length, short int color, int bounds[4]);
void draw_line(int x0, int y0, int x1, int y1, short int color);
void draw_rectangle(int x0, int y0, int x1, int y1, short int color, int bounds[4]);
void clear_screen();

#endif
// --- End of .\Test folder\graphics.h ---

// --- Start of .\Test folder\stage_1.h ---
#ifndef STAGE_1_H
#define STAGE_1_H

void run_stage_1();

#endif
// --- End of .\Test folder\stage_1.h ---

// --- Start of .\Test folder\Bone.c ---
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
// Stripped local include: #include "graphics.h"
// Stripped local include: #include "stage_0.h"


int main(void)
{
    run_stage_1();
    
}

// --- End of .\Test folder\Bone.c ---

// --- Start of .\Test folder\graphics.c ---
// Stripped local include: #include "graphics.h"
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

volatile int pixel_buffer_start; // global variable
volatile int * pixel_ctrl_ptr = (int *) 0xFF203020;
short int Buffer1[240][512]; // 240 rows, 512 (320 + padding) columns
short int Buffer2[240][512];

// array size is 2464
// Array size is now 1232 bytes
static const unsigned char Gaster_Blaster[]  = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
  0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 
  0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 
  0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 
  0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 
  0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 
  0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 
  1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 
  0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 
  0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 
  0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 
  0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 
  0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 
  0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 
  0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 
  0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 
  0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 
  1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 
  0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 
  0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 
  0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 
  0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 
  0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 
  0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 
  0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 
  0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 
  0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 
  0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

static const short int blasterColors[20] = {0xFFFF, // #ffffff
    0xef9d, // #f2f2f2
    0xe71c, // #e4e4e4
    0xD6BA, // #d7d7d7
    0xc658, // #c9c9c9
    0xbdd7, // #bcbcbc
    0xAD75, // #aeaeae
    0xA514, // #a1a1a1
    0x94B2, // #949494
    0x8430, // #868686
    0x7BcF, // #797979
    0x6B4D, // #6b6b6b
    0x5AEB, // #5e5e5e
    0x528A, // #515151
    0x4228, // #434343
    0x39A7, // #363636
    0x2945, // #282828
    0x18E3, // #1b1b1b
    0x1062, // #0d0d0d
    0x0000  // #000000
};

// we have a look up table for sin to avoid calculating floats
static const int sinValues[360] = {
       0,   4,   9,  13,  18,  22,  27,  31,  36,  40,
      44,  49,  53,  58,  62,  66,  71,  75,  79,  83,
      88,  92,  96, 100, 104, 108, 112, 116, 120, 124,
     128, 132, 136, 139, 143, 147, 150, 154, 158, 161,
     165, 168, 171, 175, 178, 181, 184, 187, 190, 193,
     196, 199, 202, 204, 207, 210, 212, 215, 217, 219,
     222, 224, 226, 228, 230, 232, 234, 236, 237, 239,
     241, 242, 243, 245, 246, 247, 248, 249, 250, 251,
     252, 253, 254, 254, 255, 255, 255, 256, 256, 256,
     256, 256, 256, 256, 255, 255, 255, 254, 254, 253,
     252, 251, 250, 249, 248, 247, 246, 245, 243, 242,
     241, 239, 237, 236, 234, 232, 230, 228, 226, 224,
     222, 219, 217, 215, 212, 210, 207, 204, 202, 199,
     196, 193, 190, 187, 184, 181, 178, 175, 171, 168,
     165, 161, 158, 154, 150, 147, 143, 139, 136, 132,
     128, 124, 120, 116, 112, 108, 104, 100,  96,  92,
      88,  83,  79,  75,  71,  66,  62,  58,  53,  49,
      44,  40,  36,  31,  27,  22,  18,  13,   9,   4,
       0,  -4,  -9, -13, -18, -22, -27, -31, -36, -40,
     -44, -49, -53, -58, -62, -66, -71, -75, -79, -83,
     -88, -92, -96,-100,-104,-108,-112,-116,-120,-124,
    -128,-132,-136,-139,-143,-147,-150,-154,-158,-161,
    -165,-168,-171,-175,-178,-181,-184,-187,-190,-193,
    -196,-199,-202,-204,-207,-210,-212,-215,-217,-219,
    -222,-224,-226,-228,-230,-232,-234,-236,-237,-239,
    -241,-242,-243,-245,-246,-247,-248,-249,-250,-251,
    -252,-253,-254,-254,-255,-255,-255,-256,-256,-256,
    -256,-256,-256,-256,-255,-255,-255,-254,-254,-253,
    -252,-251,-250,-249,-248,-247,-246,-245,-243,-242,
    -241,-239,-237,-236,-234,-232,-230,-228,-226,-224,
    -222,-219,-217,-215,-212,-210,-207,-204,-202,-199,
    -196,-193,-190,-187,-184,-181,-178,-175,-171,-168,
    -165,-161,-158,-154,-150,-147,-143,-139,-136,-132,
    -128,-124,-120,-116,-112,-108,-104,-100, -96, -92,
     -88, -83, -79, -75, -71, -66, -62, -58, -53, -49,
     -44, -40, -36, -31, -27, -22, -18, -13,  -9,  -4
};

static const int cosValues[360] = {
     256, 256, 256, 256, 255, 255, 255, 254, 254, 253,
     252, 251, 250, 249, 248, 247, 246, 245, 243, 242,
     241, 239, 237, 236, 234, 232, 230, 228, 226, 224,
     222, 219, 217, 215, 212, 210, 207, 204, 202, 199,
     196, 193, 190, 187, 184, 181, 178, 175, 171, 168,
     165, 161, 158, 154, 150, 147, 143, 139, 136, 132,
     128, 124, 120, 116, 112, 108, 104, 100,  96,  92,
      88,  83,  79,  75,  71,  66,  62,  58,  53,  49,
      44,  40,  36,  31,  27,  22,  18,  13,   9,   4,
       0,  -4,  -9, -13, -18, -22, -27, -31, -36, -40,
     -44, -49, -53, -58, -62, -66, -71, -75, -79, -83,
     -88, -92, -96,-100,-104,-108,-112,-116,-120,-124,
    -128,-132,-136,-139,-143,-147,-150,-154,-158,-161,
    -165,-168,-171,-175,-178,-181,-184,-187,-190,-193,
    -196,-199,-202,-204,-207,-210,-212,-215,-217,-219,
    -222,-224,-226,-228,-230,-232,-234,-236,-237,-239,
    -241,-242,-243,-245,-246,-247,-248,-249,-250,-251,
    -252,-253,-254,-254,-255,-255,-255,-256,-256,-256,
    -256,-256,-256,-256,-255,-255,-255,-254,-254,-253,
    -252,-251,-250,-249,-248,-247,-246,-245,-243,-242,
    -241,-239,-237,-236,-234,-232,-230,-228,-226,-224,
    -222,-219,-217,-215,-212,-210,-207,-204,-202,-199,
    -196,-193,-190,-187,-184,-181,-178,-175,-171,-168,
    -165,-161,-158,-154,-150,-147,-143,-139,-136,-132,
    -128,-124,-120,-116,-112,-108,-104,-100, -96, -92,
     -88, -83, -79, -75, -71, -66, -62, -58, -53, -49,
     -44, -40, -36, -31, -27, -22, -18, -13,  -9,  -4,
       0,   4,   9,  13,  18,  22,  27,  31,  36,  40,
      44,  49,  53,  58,  62,  66,  71,  75,  79,  83,
      88,  92,  96, 100, 104, 108, 112, 116, 120, 124,
     128, 132, 136, 139, 143, 147, 150, 154, 158, 161,
     165, 168, 171, 175, 178, 181, 184, 187, 190, 193,
     196, 199, 202, 204, 207, 210, 212, 215, 217, 219,
     222, 224, 226, 228, 230, 232, 234, 236, 237, 239,
     241, 242, 243, 245, 246, 247, 248, 249, 250, 251,
     252, 253, 254, 254, 255, 255, 255, 256, 256, 256
};


int bounds_unlimited[4] = {0, 0, 360, 240};
int bounds_default[4] = {123, 116, 199, 192};

void graphics_init() {
    volatile int * pixel_ctrl_ptr = (int *)0xFF203020;
    /* Read location of the pixel buffer from the pixel buffer controller */
    pixel_buffer_start = *pixel_ctrl_ptr;

    /* set front pixel buffer to Buffer 1 */
    *(pixel_ctrl_ptr + 1) = (int) &Buffer1; // first store the address in the  back buffer
    /* now, swap the front/back buffers, to set the front buffer location */
    wait_for_vsync();
    /* initialize a pointer to the pixel buffer, used by drawing functions */
    pixel_buffer_start = *pixel_ctrl_ptr;
    clear_screen(); // pixel_buffer_start points to the pixel buffer

    /* set back pixel buffer to Buffer 2 */
    *(pixel_ctrl_ptr + 1) = (int) &Buffer2;
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // we draw on the back buffer
    clear_screen(); // pixel_buffer_start points to the pixel buffer
}

void wait_for_vsync() {
    *pixel_ctrl_ptr = 1;
    while ((*(pixel_ctrl_ptr + 3) & 0x00000001) != 0) {
        continue;
    }
}

void swap_buffers() {
    wait_for_vsync();
    pixel_buffer_start = *(pixel_ctrl_ptr + 1); // Switch to the new back buffer
}

void plot_pixel(int x, int y, short int line_color)
{
    volatile short int *one_pixel_address;
    one_pixel_address = pixel_buffer_start + (y << 10) + (x << 1);
    *one_pixel_address = line_color;
}

void draw_line(int x0, int y0, int x1, int y1, short int color){
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
void draw_rectangle(int x0, int y0, int x1, int y1, short int color, int bounds[4]) {
    
    for (int i = x0; i <= x1; i++) {
        for (int j = y0; j <= y1; j++) {
            if (i < bounds[0] || i > bounds[2] || j < bounds[1] || j > bounds[3]) {
                continue;
            }
            plot_pixel(i, j, color);
        }
    }
}

void draw_rectangle_outline(int x0, int y0, int x1, int y1, short int color) {
    draw_line(x0, y0, x1, y0, color); 
    draw_line(x1, y0, x1, y1, color); 
    draw_line(x1, y1, x0, y1, color); 
    draw_line(x0, y1, x0, y0, color); 
}

void draw_blaster(struct blaster *blaster_ptr) {
    if (blaster_ptr->frameCount > 148) {
        return;
    }

    // draw the blaster head
    for (int i = blaster_ptr->posx; i < GASTER_BLASTER_WIDTH + blaster_ptr->posx; i++) {
        for (int j = blaster_ptr->posy; j < GASTER_BLASTER_HEIGHT + blaster_ptr->posy; j++) {
            int index = i - blaster_ptr->posx + (j - blaster_ptr->posy) * 22;
            if (Gaster_Blaster[index] == 1) {
                if (blaster_ptr->frameCount < 20) {
                    plot_pixel(i, j, blasterColors[19-blaster_ptr->frameCount]);
                }
                else if (blaster_ptr->frameCount >= 128 && blaster_ptr->frameCount < 148) {
                    plot_pixel(i, j, blasterColors[blaster_ptr->frameCount-128]);
                }
                else if (blaster_ptr->frameCount == 148) {
                    plot_pixel(i, j, 0x0000);
                }
                else {
                    plot_pixel(i, j, 0xffff);
                }
            }
        }
    }

    int beam_x0 = blaster_ptr->posx;
    int beam_y0 = blaster_ptr->posy + GASTER_BLASTER_HEIGHT;
    int beam_x1 = blaster_ptr->posx + GASTER_BLASTER_WIDTH - 1;

    // draw the blaster beam
    if (blaster_ptr->frameCount >= 68 && blaster_ptr->frameCount <= 128) {
        draw_rectangle(beam_x0, beam_y0, beam_x1, 239, 0xffff, bounds_unlimited);
    }
    else if (blaster_ptr->frameCount == 148) {
        draw_rectangle(beam_x0, beam_y0, beam_x1, 239, 0x0000, bounds_unlimited);
    }
    else if (blaster_ptr->frameCount > 128) {
        draw_rectangle(beam_x0, beam_y0, beam_x1, 239, blasterColors[blaster_ptr->frameCount-128], bounds_unlimited);
    }

    blaster_ptr->frameCount++;
}

void draw_any_blaster(struct blaster *blaster_ptr) {

    if (blaster_ptr->frameCount > 148) {
        return;
    }
	if (blaster_ptr->frameCount < 0) {
		blaster_ptr->frameCount++;
		return;
	}
	
	int cx = blaster_ptr->centerx;
	int cy = blaster_ptr->centery;
	int frame = blaster_ptr->frameCount;
	if (frame < 0) {frame = 0;}
	int cosV = cosValues[blaster_ptr->rotation];
    int sinV = sinValues[blaster_ptr->rotation];
	
	short int blasterColor;
	
	if (frame < 20) {
		blasterColor = blasterColors[19-frame];
	}
	else if (frame >= 128 && frame < 148) {
		blasterColor = blasterColors[frame-128];
	}
	else if (frame == 148) {
		blasterColor = 0x0000;
	}
	else {
		blasterColor = 0xffff;
	}
	
	short int beamColor;
	if (frame >= 68 && frame <= 128) {
		beamColor = 0xFFFF;
	}
	else if (frame > 128) {
		beamColor = blasterColors[frame - 128];
	}
	
	int min_x, max_x, min_y, max_y;

    if (frame < 68) {
        // no laser 
        min_x = cx - 40; if (min_x < 0) min_x = 0;
        max_x = cx + 40; if (max_x > 320) max_x = 320;
        min_y = cy - 40; if (min_y < 0) min_y = 0;
        max_y = cy + 40; if (max_y > 240) max_y = 240;
    } else {
        // laser is firing
        min_x = cx - 320; if (min_x < 0) min_x = 0;
        max_x = cx + 320; if (max_x > 320) max_x = 320;
        min_y = cy - 320; if (min_y < 0) min_y = 0;
        max_y = cy + 320; if (max_y > 240) max_y = 240;
    }
	

    for (int j = min_y; j < max_y; j++) {
		
		int centreDistanceY = j - cy;
		int y_x = centreDistanceY * sinV;
		int y_y = centreDistanceY * cosV;
		
        for (int i = min_x; i < max_x; i++) {

            // calculate centre of blaster head to current pixel location
            int centreDistanceX = i - cx;
            

            int sourceX = ((centreDistanceX * cosV + y_x) >> 8) + (GASTER_BLASTER_WIDTH >> 1);
            int sourceY = ((-1 * centreDistanceX * sinV + y_y) >> 8) + (GASTER_BLASTER_HEIGHT >> 1);

            // draw head
            if (sourceX >= 0 && sourceX < GASTER_BLASTER_WIDTH && sourceY >= 0 && sourceY < GASTER_BLASTER_HEIGHT) {
                int index = sourceX + sourceY * GASTER_BLASTER_WIDTH;
                if (Gaster_Blaster[index] == 1) {
                    plot_pixel(i, j, blasterColor);
                }
            }
            // draw beam
            else if (sourceX >= 0 && sourceX < GASTER_BLASTER_WIDTH && sourceY < 240 && sourceY >= GASTER_BLASTER_HEIGHT) {
                plot_pixel(i,j,beamColor);
            }
        }
    }

    blaster_ptr->frameCount++;
}

void update_pos(int newPos, int pos[]){
    pos[2] = pos[1];
    pos[1] = pos[0];
    pos[0] = newPos;
}

// this function draws a vertical bone on the screen, at the specified coordinate.
// the coordinate starts at the top left, then goes down and right.
// for every bone, there are 3 parts: the top, bottom, and middle. the top and the bottom represents the "joint" of the bone, while the middle part is the flat part.
// the length in the function represents how long the middle part is. the smallest length is 1. inputting anything smaller than a 1 as length will result in a bone of length 1.
void draw_bone(int x0, int y0, int length, short int color, int bounds[4]) {
    draw_rectangle(x0, y0, x0+1, y0+2, color, bounds);
    draw_rectangle(x0+3, y0, x0+4, y0+2, color, bounds);
    draw_rectangle(x0, y0+2+length+1, x0+1, y0+4+length+1, color, bounds);
    draw_rectangle(x0+3, y0+2+length+1, x0+4, y0+4+length+1, color, bounds);

    // draw the middle part
    draw_rectangle(x0+1, y0+1, x0+3, y0+2+length+2, color, bounds);
}

void clear_screen(){
    for (int i = 0; i < 320; i++) {
        for (int j = 0; j < 240; j++) {
            plot_pixel(i, j, 0x0000);
        }
    }
}


// --- End of .\Test folder\graphics.c ---

// --- Start of .\Test folder\stage_1.c ---
// Stripped local include: #include "graphics.h"

#include <math.h>

void run_stage_1() {
    graphics_init();

	struct blaster blaster_army[4];
	
	for (int i = 0; i < 4; i++) {
		blaster_army[i].centerx = 20;
		blaster_army[i].centery = 20 + 40 * i;
		blaster_army[i].rotation = 45;
		blaster_army[i].frameCount = 0;
	}
    

    int bounds_unlimited[4] = {0, 0, 360, 240};
    int bounds_default[4] = {123, 116, 199, 192};

    draw_rectangle(120, 113, 202, 115, 0xFFFF, bounds_unlimited);
    draw_rectangle(120, 113, 122, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(120, 193, 202, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);

    swap_buffers();

    draw_rectangle(120, 113, 202, 115, 0xFFFF, bounds_unlimited);
    draw_rectangle(120, 113, 122, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(120, 193, 202, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);

    swap_buffers();
	
	struct Bone bone_army[40];

    // loop to create the bones for the sin wave intro attack.
    // gap between top bone and bottom bone is 38/2 = 19 pixels
    for (int i = 0; i < 20; i++) {

		int sinValue = sinValues[i / 3] * 20;
		
        bone_army[i].posx[0] = 124 - 14 * i << 8;
        bone_army[i].posx[1] = 124 - 14 * i << 8;
        bone_army[i].posx[2] = 124 - 14 * i << 8;
        bone_army[i].posy[0] = 117 << 8;
        bone_army[i].posy[1] = 117 << 8;
        bone_army[i].posy[2] = 117 << 8;
        bone_army[i].length = 20 + sinValue;
        bone_army[i].velox = 512;
        bone_army[i].veloy = 0;
        bone_army[i].color = 0xFFFF;

        int posy = 117 + (int)(41 + sinValue) << 8;

        bone_army[i+20].posx[0] = 124 - 14 * i << 8;
        bone_army[i+20].posx[1] = 124 - 14 * i << 8;
        bone_army[i+20].posx[2] = 124 - 14 * i << 8;
        bone_army[i+20].posy[0] = posy;
        bone_army[i+20].posy[1] = posy;
        bone_army[i+20].posy[2] = posy;
        bone_army[i+20].length = 186- (posy >> 8);
        bone_army[i+20].velox = 512;
        bone_army[i+20].veloy = 0;
        bone_army[i+20].color = 0xFFFF;
    }
	
	

    while (1) {
        for (int i = 0; i < 4; i++) {
			draw_any_blaster(&blaster_army[i]);
		}
        
		for (int i = 0; i < 40; i++) {
            draw_bone(bone_army[i].posx[1] >> 8, bone_army[i].posy[1] >> 8, bone_army[i].length,0x0000, bounds_default); //erase old one
        }

        for (int i = 0; i < 40; i++) {
			if(bone_army[i].posx[0] >= 210 << 8) {
				update_pos(-300 << 8, bone_army[i].posx);
			} else {
				update_pos(bone_army[i].posx[0] + bone_army[i].velox, bone_army[i].posx); 
			}
			draw_bone(bone_army[i].posx[0] >> 8, bone_army[i].posy[0] >> 8, bone_army[i].length,0xFFFF, bounds_default); //draw new one
        }
		
        swap_buffers();
    }
}
// --- End of .\Test folder\stage_1.c ---

