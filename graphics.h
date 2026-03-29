#ifndef GRAPHICS_H
#define GRAPHICS_H

#define GASTER_BLASTER_HEIGHT 56
#define GASTER_BLASTER_WIDTH 22

#include <stdbool.h>

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
    int posx[3];
    int posy[3];
    int width;
    int height;
    int velox;
    int veloy;
};

void wait_for_vsync();
void plot_pixel(int x, int y, short int line_color);
void update_pos(int newPos, int pos[]);
void draw_bone(struct Bone *bone_ptr, short int ind, short int color, int bounds[4]);
void draw_line(int x0, int y0, int x1, int y1, short int color);
void draw_rectangle(int x0, int y0, int x1, int y1, short int color, int bounds[4]);
void clear_screen();
void draw_number(int x, int y, int num);
void draw_any_blaster(struct blaster *blaster_ptr, int bounds[4]);
void draw_any_blaster_new(struct blaster *blaster_ptr, int bounds[4]);
void store_beam(struct blaster *blaster_ptr, int verticesX[4], int verticesY[4]);
unsigned short int read_pixel(int x, int y);

void draw_platform(struct platform *plat, short int ind, int bounds[4]);
void erase_platform(struct platform *plat, short int ind, int bounds[4]);
void update_platform(struct platform *plat);

void draw_healthbar(int health);

#endif