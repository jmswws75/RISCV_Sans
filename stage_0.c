#include "graphics.h"

void run_stage_0() {
    struct Bone bone_army[10];

    for (int i = 0; i < 10; i++) {
        bone_army[i].posx[0] = 124 - 7 * i << 8;
        bone_army[i].posx[1] = 124 - 7 * i << 8;
        bone_army[i].posx[2] = 124 - 7 * i << 8;
        bone_army[i].posy[0] = 117 << 8;
        bone_army[i].posy[1] = 117 << 8;
        bone_army[i].posy[2] = 117 << 8;
        bone_army[i].length = 60 - (i * i) * 0.5;
        bone_army[i].velox = 128;
        bone_army[i].veloy = 0;
        bone_army[i].color = 0xFFFF;
    }

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

    while (1) {
        
        for (int i = 0; i < 10; i++) {
            draw_bone(bone_army[i].posx[1] >> 8, bone_army[i].posy[1] >> 8, bone_army[i].length,0x0000, bounds_default); //erase old one
        }

        for (int i = 0; i < 10; i++) {
            if(bone_army[i].posx[0] >= 210 << 8) {
                update_pos(119 << 8, bone_army[i].posx);
                update_pos(117 << 8, bone_army[i].posy);
            } else {
                update_pos(bone_army[i].posx[0] + bone_army[i].velox, bone_army[i].posx); 
            }
            draw_bone(bone_army[i].posx[0] >> 8, bone_army[i].posy[0] >> 8, bone_army[i].length,0xFFFF, bounds_default); //draw new one
        }

        swap_buffers();

    }
}