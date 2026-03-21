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