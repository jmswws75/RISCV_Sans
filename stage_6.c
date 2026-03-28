#define NUM_BONES 50
#define NUM_PLATFORMS 6

#define BONE_HEIGHT 12
#define BIG_BONE_HEIGHT 28
#define BONE_GAP 5
#define BONE_WIDTH 5

#define PLATFORM_WIDTH 26
#define PLATFORM_HEIGHT 4
#define PLATFORM_GAP 5

#define FIRST_TO_BIG_GAP 36
#define BIG_TO_SECOND_GAP 72
#define BIG_PLATFORM_GAP 10
#define SECOND_TO_THIRD_GAP 79
#define THIRD_TO_FOURTH_GAP 27
#define FOURTH_TO_FIFTH_GAP 27
#define FIFTH_TO_SIXTH_GAP 1
#define SIXTH_PLATFORM_WIDTH 16

#define LEVEL_SPEED 256

void run_stage_6(void) {
    struct Bone bones[NUM_BONES];
    struct Bone big_bone;
    struct Bone top_bone;
    struct Bone top_bone2;
    struct Bone top_bone3;
    struct Bone entry_left;
    struct Bone entry_right;
    int entry_triggered = 0;
    struct platform plats[NUM_PLATFORMS];
    struct platform big_plat;

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 319, 239};

    const int left_border = bounds_default[0];
    const int right_border = bounds_default[2];

    const int bone_step = BONE_WIDTH + BONE_GAP;

    // Where starting point of the thing is
    const int bone_y = 175;       
    const int big_bone_y = 159;   

    const int first_bone_x = right_border + 20;

    const int platform_y = bone_y - PLATFORM_GAP - PLATFORM_HEIGHT;          // 162
    const int big_platform_y = big_bone_y - BIG_PLATFORM_GAP - PLATFORM_HEIGHT; // 141

    const int first_platform_x = right_border + 40;

    // spacing
    const int big_platform_x = first_platform_x + PLATFORM_WIDTH + FIRST_TO_BIG_GAP;
    const int big_bone_x = big_platform_x;

    const int second_platform_x = big_bone_x + BONE_WIDTH + BIG_TO_SECOND_GAP;

    const int third_platform_x = second_platform_x + PLATFORM_WIDTH + SECOND_TO_THIRD_GAP;
    const int third_platform_y = platform_y - 6;

    const int fourth_platform_x = third_platform_x + PLATFORM_WIDTH + THIRD_TO_FOURTH_GAP;
    const int fourth_platform_y = third_platform_y + 1;

    const int fifth_platform_x = fourth_platform_x + PLATFORM_WIDTH + FOURTH_TO_FIFTH_GAP;
    const int fifth_platform_y = fourth_platform_y - 6;

    const int sixth_platform_x = fifth_platform_x + PLATFORM_WIDTH + FIFTH_TO_SIXTH_GAP - 160;
    const int sixth_platform_y = fifth_platform_y - 6;

    const int top_bone_x = third_platform_x + PLATFORM_WIDTH / 2 - 2;
    const int top_bone_y = 129;

    const int top_bone2_x = fourth_platform_x + PLATFORM_WIDTH / 2 - 2;
    const int top_bone2_y = 129;
    const int top_bone3_x = fifth_platform_x + PLATFORM_WIDTH / 2 - 2;
    const int top_bone3_y = 129;

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

    // bone creation
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

    // big bone
    big_bone.color = 0xFFFF;
    big_bone.length = BIG_BONE_HEIGHT;
    big_bone.posx[0] = big_bone_x << 8;
    big_bone.posx[1] = big_bone_x << 8;
    big_bone.posx[2] = big_bone_x << 8;
    big_bone.posy[0] = big_bone_y << 8;
    big_bone.posy[1] = big_bone_y << 8;
    big_bone.posy[2] = big_bone_y << 8;
    big_bone.velox = -LEVEL_SPEED * 1.1;
    big_bone.veloy = 0;

    // top bone 1
    top_bone.color = 0xFFFF;
    top_bone.length = 20;
    top_bone.posx[0] = top_bone_x << 8;
    top_bone.posx[1] = top_bone_x << 8;
    top_bone.posx[2] = top_bone_x << 8;
    top_bone.posy[0] = top_bone_y << 8;
    top_bone.posy[1] = top_bone_y << 8;
    top_bone.posy[2] = top_bone_y << 8;
    top_bone.velox = -LEVEL_SPEED * 1.1;
    top_bone.veloy = 0;

    // top bone 2
    top_bone2.color = 0xFFFF;
    top_bone2.length = 25;
    top_bone2.posx[0] = top_bone2_x << 8;
    top_bone2.posx[1] = top_bone2_x << 8;
    top_bone2.posx[2] = top_bone2_x << 8;
    top_bone2.posy[0] = top_bone2_y << 8;
    top_bone2.posy[1] = top_bone2_y << 8;
    top_bone2.posy[2] = top_bone2_y << 8;
    top_bone2.velox = -LEVEL_SPEED * 1.1;
    top_bone2.veloy = 0;

    // top bone 3
    top_bone3.color = 0xFFFF;
    top_bone3.length = 15;
    top_bone3.posx[0] = top_bone3_x << 8;
    top_bone3.posx[1] = top_bone3_x << 8;
    top_bone3.posx[2] = top_bone3_x << 8;
    top_bone3.posy[0] = top_bone3_y << 8;
    top_bone3.posy[1] = top_bone3_y << 8;
    top_bone3.posy[2] = top_bone3_y << 8;
    top_bone3.velox = -LEVEL_SPEED * 1.1;
    top_bone3.veloy = 0;

    // fast left bone
    entry_left.color = 0xFFFF;
    entry_left.length = 45;
    entry_left.posx[0] = (left_border - BONE_WIDTH) << 8;
    entry_left.posx[1] = (left_border - BONE_WIDTH) << 8;
    entry_left.posx[2] = (left_border - BONE_WIDTH) << 8;
    entry_left.posy[0] = 142 << 8;
    entry_left.posy[1] = 142 << 8;
    entry_left.posy[2] = 142 << 8;
    entry_left.velox = 0;
    entry_left.veloy = 0;

    // fast right bone
    entry_right.color = 0xFFFF;
    entry_right.length = 45;
    entry_right.posx[0] = right_border << 8;
    entry_right.posx[1] = right_border << 8;
    entry_right.posx[2] = right_border << 8;
    entry_right.posy[0] = 129 << 8;
    entry_right.posy[1] = 129 << 8;
    entry_right.posy[2] = 129 << 8;
    entry_right.velox = 0;
    entry_right.veloy = 0;

    // platform 1
    plats[0].width = PLATFORM_WIDTH;
    plats[0].height = PLATFORM_HEIGHT;
    plats[0].posx[0] = first_platform_x << 8;
    plats[0].posx[1] = first_platform_x << 8;
    plats[0].posx[2] = first_platform_x << 8;
    plats[0].posy[0] = platform_y << 8;
    plats[0].posy[1] = platform_y << 8;
    plats[0].posy[2] = platform_y << 8;
    plats[0].velox = -LEVEL_SPEED * 1.1;
    plats[0].veloy = 0;

    // platform 2
    plats[1].width = PLATFORM_WIDTH;
    plats[1].height = PLATFORM_HEIGHT;
    plats[1].posx[0] = second_platform_x << 8;
    plats[1].posx[1] = second_platform_x << 8;
    plats[1].posx[2] = second_platform_x << 8;
    plats[1].posy[0] = platform_y << 8;
    plats[1].posy[1] = platform_y << 8;
    plats[1].posy[2] = platform_y << 8;
    plats[1].velox = -LEVEL_SPEED * 1.1;
    plats[1].veloy = 0;

    // platform 3
    plats[2].width = PLATFORM_WIDTH;
    plats[2].height = PLATFORM_HEIGHT;
    plats[2].posx[0] = third_platform_x << 8;
    plats[2].posx[1] = third_platform_x << 8;
    plats[2].posx[2] = third_platform_x << 8;
    plats[2].posy[0] = third_platform_y << 8;
    plats[2].posy[1] = third_platform_y << 8;
    plats[2].posy[2] = third_platform_y << 8;
    plats[2].velox = -LEVEL_SPEED * 1.1;
    plats[2].veloy = 0;

    // platform 4
    plats[3].width = PLATFORM_WIDTH;
    plats[3].height = PLATFORM_HEIGHT;
    plats[3].posx[0] = fourth_platform_x << 8;
    plats[3].posx[1] = fourth_platform_x << 8;
    plats[3].posx[2] = fourth_platform_x << 8;
    plats[3].posy[0] = fourth_platform_y << 8;
    plats[3].posy[1] = fourth_platform_y << 8;
    plats[3].posy[2] = fourth_platform_y << 8;
    plats[3].velox = -LEVEL_SPEED * 1.1;
    plats[3].veloy = 0;

    // platform 5
    plats[4].width = PLATFORM_WIDTH;
    plats[4].height = PLATFORM_HEIGHT;
    plats[4].posx[0] = fifth_platform_x << 8;
    plats[4].posx[1] = fifth_platform_x << 8;
    plats[4].posx[2] = fifth_platform_x << 8;
    plats[4].posy[0] = fifth_platform_y << 8;
    plats[4].posy[1] = fifth_platform_y << 8;
    plats[4].posy[2] = fifth_platform_y << 8;
    plats[4].velox = -LEVEL_SPEED * 1.1;
    plats[4].veloy = 0;

    // platform 6
    plats[5].width = SIXTH_PLATFORM_WIDTH;
    plats[5].height = PLATFORM_HEIGHT;
    plats[5].posx[0] = sixth_platform_x << 8;
    plats[5].posx[1] = sixth_platform_x << 8;
    plats[5].posx[2] = sixth_platform_x << 8;
    plats[5].posy[0] = sixth_platform_y << 8;
    plats[5].posy[1] = sixth_platform_y << 8;
    plats[5].posy[2] = sixth_platform_y << 8;
    plats[5].velox = -(LEVEL_SPEED * 0.71);
    plats[5].veloy = 0;

    // should have been platform 2 whoops
    big_plat.width = PLATFORM_WIDTH;
    big_plat.height = PLATFORM_HEIGHT;
    big_plat.posx[0] = big_platform_x << 8;
    big_plat.posx[1] = big_platform_x << 8;
    big_plat.posx[2] = big_platform_x << 8;
    big_plat.posy[0] = big_platform_y << 8;
    big_plat.posy[1] = big_platform_y << 8;
    big_plat.posy[2] = big_platform_y << 8;
    big_plat.velox = -LEVEL_SPEED * 1.1;
    big_plat.veloy = 0;

    while (1) {
        for (int i = 0; i < NUM_BONES; i++) {
            draw_bone(&bones[i], 1, 0x0000, bounds_default);
        }
        draw_bone(&big_bone, 1, 0x0000, bounds_default);
        draw_bone(&top_bone, 1, 0x0000, bounds_default);
        draw_bone(&top_bone2, 1, 0x0000, bounds_default);
        draw_bone(&top_bone3, 1, 0x0000, bounds_default);
        draw_bone(&entry_left, 1, 0x0000, bounds_default);
        draw_bone(&entry_right, 1, 0x0000, bounds_default);

        for (int i = 0; i < NUM_PLATFORMS; i++) {
            erase_platform(&plats[i], 1, bounds_default);
        }
        erase_platform(&big_plat, 1, bounds_default);

        for (int i = 0; i < NUM_BONES; i++) {
            update_pos(bones[i].posx[0] + bones[i].velox, bones[i].posx);
            draw_bone(&bones[i], 0, 0xFFFF, bounds_default);
        }

        update_pos(big_bone.posx[0] + big_bone.velox, big_bone.posx);
        draw_bone(&big_bone, 0, 0xFFFF, bounds_default);

        update_pos(top_bone.posx[0] + top_bone.velox, top_bone.posx);
        draw_bone(&top_bone, 0, 0xFFFF, bounds_default);

        update_pos(top_bone2.posx[0] + top_bone2.velox, top_bone2.posx);
        draw_bone(&top_bone2, 0, 0xFFFF, bounds_default);

        update_pos(top_bone3.posx[0] + top_bone3.velox, top_bone3.posx);
        draw_bone(&top_bone3, 0, 0xFFFF, bounds_default);

        // when the two fast bones should come in based on the position of the smaller platform
        if (!entry_triggered && (plats[5].posx[0] >> 8) <= 160) {
            entry_left.velox = 1.75 * LEVEL_SPEED;
            entry_right.velox = -1.75 * LEVEL_SPEED;
            entry_triggered = 1;
        }
        update_pos(entry_left.posx[0] + entry_left.velox, entry_left.posx);
        draw_bone(&entry_left, 0, 0xFFFF, bounds_default);
        update_pos(entry_right.posx[0] + entry_right.velox, entry_right.posx);
        draw_bone(&entry_right, 0, 0xFFFF, bounds_default);

        for (int i = 0; i < NUM_PLATFORMS; i++) {
            update_platform(&plats[i]);
            draw_platform(&plats[i], 0, bounds_default);
        }

        update_platform(&big_plat);
        draw_platform(&big_plat, 0, bounds_default);

        swap_buffers();

        if (bones[NUM_BONES - 1].posx[0] <= ((left_border - 20) << 8)) {
            break;
        }
    }
}