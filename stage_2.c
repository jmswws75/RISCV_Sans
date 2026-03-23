#include "graphics.h"
#include <math.h>

void run_stage_2() {
    struct Bone Bone_army[32];

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 360, 240};

    // left bones
    for (int i = 0; i < 16; i+=2) {
        // bottom
        Bone_army[i].color = 0xffff;
        Bone_army[i].length = 4;
        Bone_army[i].posx[0] = (0 - 50 * i) << 8;
        Bone_army[i].posx[1] = (0 - 50 * i) << 8;
        Bone_army[i].posx[2] = (0 - 50 * i) << 8;
        Bone_army[i].posy[0] = 183 << 8;
        Bone_army[i].posy[1] = 183 << 8;
        Bone_army[i].posy[2] = 183 << 8;
        Bone_army[i].velox = 256;
        Bone_army[i].veloy = 0;

        // top
        Bone_army[i+1].color = 0xffff;
        Bone_army[i+1].length = 42;
        Bone_army[i+1].posx[0] = (0 - 50 * i) << 8;
        Bone_army[i+1].posx[1] = (0 - 50 * i) << 8;
        Bone_army[i+1].posx[2] = (0 - 50 * i) << 8;
        Bone_army[i+1].posy[0] = 129 << 8;
        Bone_army[i+1].posy[1] = 129 << 8;
        Bone_army[i+1].posy[2] = 129 << 8;
        Bone_army[i+1].velox = 256;
        Bone_army[i+1].veloy = 0;
    }

    // right bones
    for (int i = 16; i < 32; i+=2) {
        // bottom
        Bone_army[i].color = 0xffff;
        Bone_army[i].length = 4;
        Bone_army[i].posx[0] = (320 + 50 * (i - 16)) << 8;
        Bone_army[i].posx[1] = (320 + 50 * (i - 16)) << 8;
        Bone_army[i].posx[2] = (320 + 50 * (i - 16)) << 8;
        Bone_army[i].posy[0] = 183 << 8;
        Bone_army[i].posy[1] = 183 << 8;
        Bone_army[i].posy[2] = 183 << 8;
        Bone_army[i].velox = -256;
        Bone_army[i].veloy = 0;

        // top
        Bone_army[i+1].color = 0xffff;
        Bone_army[i+1].length = 42;
        Bone_army[i+1].posx[0] = (320 + 50 * (i - 16)) << 8;
        Bone_army[i+1].posx[1] = (320 + 50 * (i - 16)) << 8;
        Bone_army[i+1].posx[2] = (320 + 50 * (i - 16)) << 8;
        Bone_army[i+1].posy[0] = 129 << 8;
        Bone_army[i+1].posy[1] = 129 << 8;
        Bone_army[i+1].posy[2] = 129 << 8;
        Bone_army[i+1].velox = -256;
        Bone_army[i+1].veloy = 0;
    }

    clear_screen();

    draw_rectangle(67, 126, 254, 128, 0xFFFF, bounds_unlimited);
    draw_rectangle(67, 126, 69, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(67, 193, 254, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(252, 126, 254, 195, 0xFFFF, bounds_unlimited);

    swap_buffers();

    clear_screen();

    draw_rectangle(67, 126, 254, 128, 0xFFFF, bounds_unlimited);
    draw_rectangle(67, 126, 69, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(67, 193, 254, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(252, 126, 254, 195, 0xFFFF, bounds_unlimited);

    swap_buffers();

    while (1) {
        
        for (int i = 0; i < 32; i++) {
            draw_bone(&Bone_army[i], 1, 0x0000, bounds_default); //erase old one
        }

        for (int i = 0; i < 32; i++) {
            update_pos(Bone_army[i].posx[0] + Bone_army[i].velox, Bone_army[i].posx); 
            draw_bone(&Bone_army[i], 0, 0xffff, bounds_default); //draw new one
        }

        if(Bone_army[15].posx[31] <= -1000 << 8) {
            break;
        }

        swap_buffers();

    }

    
}