#include "graphics.h"
#define NUM_BOTTOM_BONES 8
#define NUM_TOP_BONES 8
#define BONE_WIDTH 5
#define BONE_SPACING 35
#define BOTTOM_BONE_HEIGHT 7
#define TOP_BONE_HEIGHT 42
#define LEVEL_SPEED 256

void run_stage_10(void) {
    struct Bone bottom_bones[NUM_BOTTOM_BONES];
    struct Bone top_bones[NUM_TOP_BONES];

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 319, 239};
    
    const int left_border = bounds_default[0];
    const int right_border = bounds_default[2];
    const int bottom_border = bounds_default[3];
    const int bone_step = BONE_WIDTH + BONE_SPACING;
    const int top_y = 129;
    const int bottom_y = bottom_border - BOTTOM_BONE_HEIGHT - 5;
    const int first_bottom_x = left_border - (NUM_BOTTOM_BONES * bone_step);
    const int first_top_x = right_border + 30;

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

    // bottom bones
    for (int i = 0; i < NUM_BOTTOM_BONES; i++) {
        int x = first_bottom_x + (i * bone_step);
        bottom_bones[i].color = 0xFFFF;
        bottom_bones[i].length = BOTTOM_BONE_HEIGHT;
        bottom_bones[i].posx[0] = x << 8;
        bottom_bones[i].posx[1] = x << 8;
        bottom_bones[i].posx[2] = x << 8;
        bottom_bones[i].posy[0] = bottom_y << 8;
        bottom_bones[i].posy[1] = bottom_y << 8;
        bottom_bones[i].posy[2] = bottom_y << 8;
        bottom_bones[i].velox = LEVEL_SPEED;
        bottom_bones[i].veloy = 0;
    }

    // top bones
    for (int i = 0; i < NUM_TOP_BONES; i++) {
        int x = first_top_x + (i * bone_step);
        top_bones[i].color = 0xFFFF;
        top_bones[i].length = TOP_BONE_HEIGHT;
        top_bones[i].posx[0] = x << 8;
        top_bones[i].posx[1] = x << 8;
        top_bones[i].posx[2] = x << 8;
        top_bones[i].posy[0] = top_y << 8;
        top_bones[i].posy[1] = top_y << 8;
        top_bones[i].posy[2] = top_y << 8;
        top_bones[i].velox = -LEVEL_SPEED;
        top_bones[i].veloy = 0;
    }

    while (1) {
        for (int i = 0; i < NUM_BOTTOM_BONES; i++) {
            draw_bone(&bottom_bones[i], 1, 0x0000, bounds_default);
        }
        for (int i = 0; i < NUM_TOP_BONES; i++) {
            draw_bone(&top_bones[i], 1, 0x0000, bounds_default);
        }
        for (int i = 0; i < NUM_BOTTOM_BONES; i++) {
            update_pos(bottom_bones[i].posx[0] + bottom_bones[i].velox, bottom_bones[i].posx);
            draw_bone(&bottom_bones[i], 0, 0xFFFF, bounds_default);
        }
        for (int i = 0; i < NUM_TOP_BONES; i++) {
            update_pos(top_bones[i].posx[0] + top_bones[i].velox, top_bones[i].posx);
            draw_bone(&top_bones[i], 0, 0xFFFF, bounds_default);
        }
        swap_buffers();

        // stop condition
        int all_gone = 1;
        for (int i = 0; i < NUM_BOTTOM_BONES && all_gone; i++) {
            if (bottom_bones[i].posx[0] <= ((right_border + BONE_WIDTH) << 8)) {
                all_gone = 0;
            }
        }
        for (int i = 0; i < NUM_TOP_BONES && all_gone; i++) {
            if (top_bones[i].posx[0] + (BONE_WIDTH << 8) >= (left_border << 8)) {
                all_gone = 0;
            }
        }
        if (all_gone) {
            break;
        }
    }
}