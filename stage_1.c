#include "graphics.h"

void run_stage_1() {
    graphics_init();

    struct blaster blaster1;
    blaster1.posx = 10;
    blaster1.posy = 10;
    blaster1.frameCount = 0;

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

    while (1) {
        draw_blaster(&blaster1);
        swap_buffers();
    }
}