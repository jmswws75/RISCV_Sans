#include <stdbool.h>

#define NUM_BONES 40
#define NUM_FAST_BONES 3
#define NUM_PLATFORMS 3

#define BONE_HEIGHT 12
#define BONE_SPACING 4
#define PLATFORM_GAP 5
#define PLATFORM_SPACING 100
#define PLATFORM_WIDTH 31
#define PLATFORM_HEIGHT 4

#define LEVEL_SPEED 256
#define FAST_LEVEL_SPEED (LEVEL_SPEED * 2)
#define TOP_BOTTOM_GAP 34

void run_stage_5() {
    struct Bone bones[NUM_BONES];
    struct Bone top_fast[NUM_FAST_BONES];
    struct platform plats[NUM_PLATFORMS];
    struct Bone end_bone;

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 319, 239};

    const int left_border = bounds_default[0];
    const int right_border = bounds_default[2];

    const int bone_draw_width = 5;
    const int bone_step = bone_draw_width + BONE_SPACING;

    const int first_bone_x = left_border - (NUM_BONES * bone_step);
    const int bone_y = 176;

    const int platform_y = bone_y - PLATFORM_GAP - PLATFORM_HEIGHT;
    const int first_platform_x = left_border - 243;

    // top bones start at the top wall
    const int top_bone_y = 129;

    // bottom bones stay on the floor row
    const int bottom_bone_y = bone_y;

    // put the fast set after the end of the normal array so it enters later
    const int first_fast_x = first_bone_x;

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

    // main 40 bottom bones
    for (int i = 0; i < NUM_BONES; i++) {
        int x = first_bone_x + (i * bone_step);

        bones[i].color = 0xFFFF;
        bones[i].length = BONE_HEIGHT;
        bones[i].posx[0] = x << 8;
        bones[i].posx[1] = x << 8;
        bones[i].posx[2] = x << 8;
        bones[i].posy[0] = bottom_bone_y << 8;
        bones[i].posy[1] = bottom_bone_y << 8;
        bones[i].posy[2] = bottom_bone_y << 8;
        bones[i].velox = LEVEL_SPEED * 1.5;
        bones[i].veloy = 0;
    }

    // platforms
    for (int i = 0; i < NUM_PLATFORMS; i++) {
        int x = first_platform_x + (i * PLATFORM_SPACING);

        plats[i].width = PLATFORM_WIDTH;
        plats[i].height = PLATFORM_HEIGHT;
        plats[i].posx[0] = x << 8;
        plats[i].posx[1] = x << 8;
        plats[i].posx[2] = x << 8;
        plats[i].posy[0] = platform_y << 8;
        plats[i].posy[1] = platform_y << 8;
        plats[i].posy[2] = platform_y << 8;
        plats[i].velox = LEVEL_SPEED * 1.5;
        plats[i].veloy = 0;
    }

    // fast top 3-bone set
    for (int i = 0; i < NUM_FAST_BONES; i++) {
        int x = first_fast_x + (i * bone_step);

        top_fast[i].color = 0xFFFF;
        top_fast[i].length = BONE_HEIGHT;
        top_fast[i].posx[0] = x << 8;
        top_fast[i].posx[1] = x << 8;
        top_fast[i].posx[2] = x << 8;
        top_fast[i].posy[0] = top_bone_y << 8;
        top_fast[i].posy[1] = top_bone_y << 8;
        top_fast[i].posy[2] = top_bone_y << 8;
        top_fast[i].velox = FAST_LEVEL_SPEED;
        top_fast[i].veloy = 0;
    }

    int end_x = first_bone_x + (NUM_BONES * bone_step) - 575;

    end_bone.color = 0xFFFF;
    end_bone.length = 45;
    end_bone.posx[0] = end_x << 8;
    end_bone.posx[1] = end_x << 8;
    end_bone.posx[2] = end_x << 8;
    end_bone.posy[0] = top_bone_y << 8;
    end_bone.posy[1] = top_bone_y << 8;
    end_bone.posy[2] = top_bone_y << 8;
    end_bone.velox = LEVEL_SPEED * 2;
    end_bone.veloy = 0;

while (1) {
    for (int i = 0; i < NUM_BONES; i++) {
        draw_bone(&bones[i], 1, 0x0000, bounds_default);
    }

    for (int i = 0; i < NUM_FAST_BONES; i++) {
        draw_bone(&top_fast[i], 1, 0x0000, bounds_default);
    }

    draw_bone(&end_bone, 1, 0x0000, bounds_default);  

    for (int i = 0; i < NUM_PLATFORMS; i++) {
        erase_platform(&plats[i], 1, bounds_default);
    }

    for (int i = 0; i < NUM_BONES; i++) {
        update_pos(bones[i].posx[0] + bones[i].velox, bones[i].posx);
        draw_bone(&bones[i], 0, 0xFFFF, bounds_default);
    }

    for (int i = 0; i < NUM_FAST_BONES; i++) {
        update_pos(top_fast[i].posx[0] + top_fast[i].velox, top_fast[i].posx);
        draw_bone(&top_fast[i], 0, 0xFFFF, bounds_default);
    }

    update_pos(end_bone.posx[0] + end_bone.velox, end_bone.posx); 
    draw_bone(&end_bone, 0, 0xFFFF, bounds_default);             

    for (int i = 0; i < NUM_PLATFORMS; i++) {
        update_platform(&plats[i]);
        draw_platform(&plats[i], 0, bounds_default);
    }

    swap_buffers();
}
}
// --- End of stage_5.c ---