#include "graphics.h"

#define NUM_BONES 60
#define BONE_HEIGHT 16
#define BONE_GAP 5
#define BONE_WIDTH 5
#define LEVEL_SPEED 256

void run_stage_6(void) {
    struct Bone bones[NUM_BONES];

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 319, 239};

    const int left_border = bounds_default[0];
    const int right_border = bounds_default[2];

    const int bone_step = BONE_WIDTH + BONE_GAP;   // 5 + 5 = 10
    const int bone_y = 160;                        // change this if you want them higher/lower
    const int first_bone_x = right_border + 20;    // first bone starts off-screen on the right

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

    for (int i = 0; i < NUM_BONES; i++) {
        int x = first_bone_x + (i * bone_step);

        bones[i].color = 0xFFFF;
        bones[i].length = BONE_HEIGHT;
        bones[i].posx[0] = x << 8;
        bones[i].posx[1] = x << 8;
        bones[i].posx[2] = x << 8;
        bones[i].posy[0] = bone_y << 8;
        bones[i].posy[1] = bone_y << 8;
        bones[i].posy[2] = bone_y << 8;
        bones[i].velox = -LEVEL_SPEED;
        bones[i].veloy = 0;
    }

    while (1) {
        for (int i = 0; i < NUM_BONES; i++) {
            draw_bone(&bones[i], 1, 0x0000, bounds_default);
        }

        for (int i = 0; i < NUM_BONES; i++) {
            update_pos(bones[i].posx[0] + bones[i].velox, bones[i].posx);
            draw_bone(&bones[i], 0, 0xFFFF, bounds_default);
        }

        swap_buffers();

        if (bones[NUM_BONES - 1].posx[0] <= ((left_border - 20) << 8)) {
            break;
        }
    }
}