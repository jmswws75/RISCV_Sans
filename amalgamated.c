// AUTO-GENERATED AMALGAMATED C FILE


// ==================================================
// BEGIN FILE: graphics.h
// ==================================================

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
    int centerx;
    int centery;
    int size;
    int rotation;
    // the blaster will stay on screen for 100 frames total.
    // it takes 20 + 48 frames to appear before firing. after it fires, it will stay there for 80 frames.
    int frameCount;

    // these are for storing the beams location, you dont need to initialize them!
    int beam_min_y;
    int beam_max_y;
    int beam_min_x[240];
    int beam_max_x[240];
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
// END FILE: graphics.h


// ==================================================
// BEGIN FILE: stage_0.h
// ==================================================

#ifndef STAGE_0_H
#define STAGE_0_H

void run_stage_0();

#endif
// END FILE: stage_0.h


// ==================================================
// BEGIN FILE: stage_1.h
// ==================================================

#ifndef STAGE_1_H
#define STAGE_1_H

void run_stage_1();

#endif
// END FILE: stage_1.h


// ==================================================
// BEGIN FILE: Bone.c
// ==================================================

#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
// [Amalgamator] Removed: #include "graphics.h"
// [Amalgamator] Removed: #include "stage_0.h"


int main(void)
{
    run_stage_1();
    
}

// END FILE: Bone.c


// ==================================================
// BEGIN FILE: graphics.c
// ==================================================

// [Amalgamator] Removed: #include "graphics.h"
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
    // 1. Pre-clamp the coordinates to the bounds! 
    // This removes the heavy 'if' statement from the inner loop.
    int start_x = x0; if (start_x < bounds[0]) start_x = bounds[0];
    int end_x = x1;   if (end_x > bounds[2]) end_x = bounds[2];
    int start_y = y0; if (start_y < bounds[1]) start_y = bounds[1];
    int end_y = y1;   if (end_y > bounds[3]) end_y = bounds[3];

    if (start_x > end_x || start_y > end_y) return; // Completely off-screen

    // 2. Y loop on the OUTSIDE, X loop on the INSIDE (Horizontal drawing!)
    for (int j = start_y; j <= end_y; j++) {
        // Fast pointer initialization for the row
        volatile short int *pixel_ptr = (volatile short int *)(pixel_buffer_start + (j << 10) + (start_x << 1));
        
        for (int i = start_x; i <= end_x; i++) {
            *pixel_ptr = color; // Fast write!
            pixel_ptr++;        // Move to the next horizontal pixel
        }
    }
}

void draw_rectangle_outline(int x0, int y0, int x1, int y1, short int color) {
    draw_line(x0, y0, x1, y0, color); 
    draw_line(x1, y0, x1, y1, color); 
    draw_line(x1, y1, x0, y1, color); 
    draw_line(x0, y1, x0, y0, color); 
}

void store_beam(struct blaster *blaster_ptr, int verticesX[4], int verticesY[4]) {
    // get the max and min y value for the rotated beam
    int raw_min_y = verticesY[0];
    int raw_max_y = verticesY[0];
    for (int i = 0; i < 4; i ++) {
        if (verticesY[i] > raw_max_y) { raw_max_y = verticesY[i];}
        if (verticesY[i] < raw_min_y) { raw_min_y = verticesY[i];}
    }

    // make sure it doesnt overflow
    if ( raw_min_y < 0) {raw_min_y = 0;}
    if (raw_max_y > 239) {raw_max_y = 239;}

    blaster_ptr->beam_max_y = raw_max_y;
    blaster_ptr->beam_min_y = raw_min_y;

    for (int j = blaster_ptr->beam_min_y; j < blaster_ptr->beam_max_y; j++) {
        int leftBound = 320, rightBound = 0;
        for (int i = 0; i < 4; i++) {
            int y0 = verticesY[i], y1 = verticesY[(i + 1) % 4];
            int x0 = verticesX[i], x1 = verticesX[(i + 1) % 4];

            if (y0 <= j && y1 > j || y0 > j && y1 <= j) {
                int xInt = x0 + (j - y0) * (x1 - x0) / (y1 - y0); // point slope form of a line, isolated for x
                if (xInt < leftBound) {leftBound = xInt;}
                if (xInt > rightBound) {rightBound = xInt;}
            }
        }
        blaster_ptr->beam_min_x[j] = leftBound;
        blaster_ptr->beam_max_x[j] = rightBound;
    }


}

void draw_any_blaster(struct blaster *blaster_ptr, int bounds[4]) {

    // avoid drawing for any invisible blasters
    if (blaster_ptr->frameCount > 148) { return; }
	if (blaster_ptr->frameCount < 0) { blaster_ptr->frameCount++; return;}
	
    // calculates all constants
	int cx = blaster_ptr->centerx;
	int cy = blaster_ptr->centery;
	int frame = blaster_ptr->frameCount;
	if (frame < 0) {frame = 0;}
	int cosV = cosValues[blaster_ptr->rotation];
    int sinV = sinValues[blaster_ptr->rotation];
	
	short int blasterColor;
	
	if (frame < 20) { blasterColor = blasterColors[19-frame]; }
	else if (frame >= 128 && frame < 148) { blasterColor = blasterColors[frame-128]; }
	else if (frame == 148) { blasterColor = 0x0000; }
	else { blasterColor = 0xffff; }
	
	short int beamColor;
	if (frame >= 68 && frame <= 128) { beamColor = 0xFFFF; }
	else if (frame > 128 && frame < 148) { beamColor = blasterColors[frame - 128]; }
    else { beamColor = 0x0000; }

    int min_x = cx - 40; if (min_x < 0) min_x = 0;
    int max_x = cx + 40; if (max_x > 320) max_x = 320;
    int max_y = cy + 40; if (max_y > 240) max_y = 240;
    int min_y = cy - 40; if (min_y < 0) min_y = 0;


    for (int j = min_y; j < max_y; j++) {
        
        int centreDistanceY = j - cy;
        int y_x = centreDistanceY * sinV;
        int y_y = centreDistanceY * cosV;
        
        volatile short int *pixel_ptr = (volatile short int *)(pixel_buffer_start + (j << 10) + (min_x << 1));

        // Start our accumulators at the far-left edge of the box
        int unshifted_X = (min_x - cx) * cosV + y_x;
        int unshifted_Y = -1 * (min_x - cx) * sinV + y_y;

        for (int i = min_x; i < max_x; i++) {

            int sourceX = (unshifted_X >> 8) + (GASTER_BLASTER_WIDTH >> 1);
            int sourceY = (unshifted_Y >> 8) + (GASTER_BLASTER_HEIGHT >> 1);

            if (sourceX >= 0 && sourceX < GASTER_BLASTER_WIDTH && sourceY >= 0 && sourceY < GASTER_BLASTER_HEIGHT) {
                int index = sourceX + sourceY * GASTER_BLASTER_WIDTH;
                if (Gaster_Blaster[index] == 1) {
                    *pixel_ptr = blasterColor;
                }
            }
            
            pixel_ptr++; 
            // Just add/subtract the slope values! No multiplication needed!
            unshifted_X += cosV;  
            unshifted_Y -= sinV;  
        }
    }

    if (frame == 68) {
        int halfWidth = GASTER_BLASTER_WIDTH / 2;
        int halfHeight = GASTER_BLASTER_HEIGHT / 2;
        int beamLength = 200;

        int xUnrotated[4] = { -halfWidth, halfWidth, halfWidth, -halfWidth};
        int yUnrotated[4] = { halfHeight, halfHeight, halfHeight + beamLength, halfHeight + beamLength};
        int verticesX[4], verticesY[4];

        for (int i = 0; i < 4; i++) {
            verticesX[i] = cx + ((xUnrotated[i] * cosV - yUnrotated[i] * sinV) >> 8);
            verticesY[i] = cy + ((xUnrotated[i] * sinV + yUnrotated[i] * cosV) >> 8);
        }

        store_beam(blaster_ptr, verticesX, verticesY);
    }

    if ((frame >= 68 && frame < 148)) {
        for (int j = blaster_ptr->beam_min_y; j < blaster_ptr->beam_max_y; j++) {
            int xLeft = blaster_ptr->beam_min_x[j];
            int xRight = blaster_ptr->beam_max_x[j];

            if (xLeft < 0) xLeft = 0;
            if (xRight >= 320) xRight = 319;

            volatile short int *pixel_ptr = (volatile short int *)(pixel_buffer_start + (j << 10) + (xLeft << 1));

            for (int i = xLeft; i <= xRight; i++) {
                *pixel_ptr = beamColor; 
                pixel_ptr++;            // move to the next pixel in memory
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


// END FILE: graphics.c


// ==================================================
// BEGIN FILE: movement.c
// ==================================================

// #include <stdbool.h>
// #include <stdlib.h>

// #define PS2_BASE 0xFF200100

// volatile int pixel_buffer_start;
// volatile int *pixel_ctrl_ptr = (int *)0xFF203020;
// volatile int *PS2_ptr = (int *)PS2_BASE;

// void plot_pixel(int x, int y, short int color);
// void clear_screen(void);
// void draw_rectangle(int x0, int y0, int x1, int y1, short int color);
// void draw_player(int x, int y, short int color);

// void plot_pixel(int x, int y, short int color)
// {
//     volatile short int *one_pixel_address;
//     one_pixel_address = (volatile short int *)(pixel_buffer_start + (y << 10) + (x << 1));
//     *one_pixel_address = color;
// }

// void clear_screen(void)
// {
//     int x, y;
//     for (x = 0; x < 320; x++) {
//         for (y = 0; y < 240; y++) {
//             plot_pixel(x, y, 0x0000);
//         }
//     }
// }

// void draw_rectangle(int x0, int y0, int x1, int y1, short int color)
// {
//     int x, y;
//     for (x = x0; x <= x1; x++) {
//         for (y = y0; y <= y1; y++) {
//             plot_pixel(x, y, color);
//         }
//     }
// }

// void draw_player(int x, int y, short int color)
// {
//     draw_rectangle(x, y, x + 1, y + 1, color);
// }

// int main(void)
// {
//     int x = 10;
//     int y = 120;
//     int old_x = x;
//     int old_y = y;

//     int PS2_data;
//     int RVALID;
//     char byte;
//     char last_byte = 0;

//     pixel_buffer_start = *pixel_ctrl_ptr;
//     clear_screen();
//     draw_player(x, y, 0xFFFF);

//     while (1) {
//         old_x = x;
//         old_y = y;

//         while (1) {
// 			// keep reading until buffer is empty (clears all pending input and nothing gets stuck in FIFO)
//             PS2_data = *PS2_ptr;
//             RVALID = PS2_data & 0x8000;	// check if new data is available
//             if (!RVALID){	// if no data exit loop
//                 break;
// 			}

//             byte = PS2_data & 0xFF;	// Read the key code
			
// 			// Only act on real key presses not the release
//             if (byte != (char)0xF0 && last_byte != (char)0xF0) {	// Checks that this is not a release signal, Prevents using the byte right after a release (avoid mistake)
//                 if (byte == 0x1D) {
//                     if (y > 0) y--;
//                 }
//                 else if (byte == 0x1C) {
//                     if (x > 0) x--;
//                 }
//                 else if (byte == 0x1B) {
//                     if (y < 238) y++;
//                 }
//                 else if (byte == 0x23) {
//                     if (x < 318) x++;
//                 }
//             }

//             last_byte = byte;
//         }

//         if (x != old_x || y != old_y) {	// Avoid unnecessary drawing when nothing changes
//             draw_player(old_x, old_y, 0x0000);
//             draw_player(x, y, 0xFFFF);
//         }
//     }

//     return 0;
// }
// END FILE: movement.c


// ==================================================
// BEGIN FILE: stage_0.c
// ==================================================

// [Amalgamator] Removed: #include "graphics.h"
#include <math.h>

int subStageCount = 0;

void run_stage_0() {

    int bounds_unlimited[4] = {0, 0, 360, 240};
    int bounds_default[4] = {123, 116, 199, 192};

    graphics_init();

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

    
    // wait for half a sec
    int frameCount = 0;
    while (1) {
        if (frameCount > 30) {
            break;
        }
        swap_buffers();
        frameCount++;
    }

    frameCount = 0; // reset frameCount

    // substage0
    while (1) {
        if (frameCount > 9) {
            break;
        }

        draw_rectangle_outline(124, 166, 198, 191, 0xf800);
        swap_buffers();
        frameCount++;
    }

    frameCount = 0;
    draw_rectangle_outline(124, 166, 198, 191, 0x0000);
    swap_buffers();
    draw_rectangle_outline(124, 166, 198, 191, 0x0000);

    // substage1
    struct Bone bone_army_1[20];
    for (int i = 0; i < 20; i++) {
        bone_army_1[i].posx[0] = 199 - 7 * i << 8;
        bone_army_1[i].posx[1] = 199 - 7 * i << 8;
        bone_army_1[i].posx[2] = 199 - 7 * i << 8;
        bone_army_1[i].posy[0] = 196 << 8;
        bone_army_1[i].posy[1] = 196 << 8;
        bone_army_1[i].posy[2] = 196 << 8;
        bone_army_1[i].length = 30;
        bone_army_1[i].velox = 0;
        bone_army_1[i].veloy = -512;
        bone_army_1[i].color = 0xFFFF;
    }

    while (1) {
        
        if (frameCount > 120) {
            break;
        }

        for (int i = 0; i < 20; i++) {
            draw_bone(bone_army_1[i].posx[1] >> 8, bone_army_1[i].posy[1] >> 8, bone_army_1[i].length,0x0000, bounds_default); //erase old one
        }

        for (int i = 0; i < 20; i++) {
            if(bone_army_1[i].posy[0] <= 166 << 8) {
                bone_army_1[i].veloy = 0;
            } else {
                update_pos(bone_army_1[i].posy[0] + bone_army_1[i].veloy, bone_army_1[i].posy); 
            }
            draw_bone(bone_army_1[i].posx[0] >> 8, bone_army_1[i].posy[0] >> 8, bone_army_1[i].length,0xFFFF, bounds_default); //draw new one
        }

        swap_buffers();
        frameCount++;

    }

    // erase all bones from substage1
    for (int i = 0; i < 20; i++) {
        draw_bone(bone_army_1[i].posx[0] >> 8, bone_army_1[i].posy[0] >> 8, bone_army_1[i].length,0x0000, bounds_default); //erase old one
    }
    swap_buffers();
    for (int i = 0; i < 20; i++) {
        draw_bone(bone_army_1[i].posx[0] >> 8, bone_army_1[i].posy[0] >> 8, bone_army_1[i].length,0x0000, bounds_default); //erase old one
    }
    swap_buffers();

    struct Bone bone_army[40];

    // loop to create the bones for the sin wave intro attack.
    // gap between top bone and bottom bone is 38/2 = 19 pixels
    for (int i = 0; i < 20; i++) {

		int sinValue = sin( (double)i / 3) * 20;
		
        bone_army[i].posx[0] = 60 - 14 * i << 8;
        bone_army[i].posx[1] = 60 - 14 * i << 8;
        bone_army[i].posx[2] = 60 - 14 * i << 8;
        bone_army[i].posy[0] = 117 << 8;
        bone_army[i].posy[1] = 117 << 8;
        bone_army[i].posy[2] = 117 << 8;
        bone_army[i].length = 20 + sinValue;
        bone_army[i].velox = 512;
        bone_army[i].veloy = 0;
        bone_army[i].color = 0xFFFF;

        int posy = 117 + (int)(41 + sinValue) << 8;

        bone_army[i+20].posx[0] = 60 - 14 * i << 8;
        bone_army[i+20].posx[1] = 60 - 14 * i << 8;
        bone_army[i+20].posx[2] = 60 - 14 * i << 8;
        bone_army[i+20].posy[0] = posy;
        bone_army[i+20].posy[1] = posy;
        bone_army[i+20].posy[2] = posy;
        bone_army[i+20].length = 186- (posy >> 8);
        bone_army[i+20].velox = 512;
        bone_army[i+20].veloy = 0;
        bone_army[i+20].color = 0xFFFF;
    }

    

    

    while (1) {
        
        

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
// END FILE: stage_0.c


// ==================================================
// BEGIN FILE: stage_1.c
// ==================================================

// [Amalgamator] Removed: #include "graphics.h"
#include <math.h>

void run_stage_1() {
    graphics_init();

	struct blaster blaster_army[10];
	
	for (int i = 0; i < 4; i++) {
		blaster_army[i].centerx = 300;
		blaster_army[i].centery = 20 + 20 * i;
		blaster_army[i].rotation = 90;
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

		int sinValue = sin((double)i / 3) * 20;
		
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

        for (int i = 0; i < 40; i++) {
            draw_bone(bone_army[i].posx[1] >> 8, bone_army[i].posy[1] >> 8, bone_army[i].length,0x0000, bounds_default); //erase old one
        }

        for (int i = 0; i < 4; i++) {
			draw_any_blaster(&blaster_army[i], bounds_default);
		}

        draw_rectangle(120, 113, 202, 115, 0xFFFF, bounds_unlimited);
        draw_rectangle(120, 113, 122, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(120, 193, 202, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);

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
// END FILE: stage_1.c

