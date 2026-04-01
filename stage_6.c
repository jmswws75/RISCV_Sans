#include <stdlib.h>
#include "movement.h"
#include "graphics.h"

#define NUM_FLOOR_BONES 50
#define NUM_BONES 56   // 50 floor + big + top1 + top2 + top3 + entry_left + entry_right
#define NUM_PLATFORMS 7  // 6 regular + big_plat

#define IDX_BIG_BONE    50
#define IDX_TOP_BONE    51
#define IDX_TOP_BONE2   52
#define IDX_TOP_BONE3   53
#define IDX_ENTRY_LEFT  54
#define IDX_ENTRY_RIGHT 55
#define IDX_BIG_PLAT    6

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

int run_stage_6(int *Global_health) {
    struct Bone bones[NUM_BONES];
    int entry_triggered = 0;
    struct platform platforms[NUM_PLATFORMS];

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 319, 239};

    struct player player1;
    struct Sans sans;
    sans.centerx = 161;
    sans.centery = 83;

    struct Head head;
    head.centerx = 161;
    head.centery = 83;
    player1.ground = (192 - 5) << 8;
    for (int i = 0; i < 3; i++) {
        player1.posx[i] = 157 << 8;
        player1.posy[i] = 150 << 8;
    }
    player1.was_up_pressed = false;
    player1.have_gravity = true;
    
    for (int i = 0; i< 4; i++) {
        player1.bounds[i] = bounds_default[i];
    }
    player1.health = *Global_health;
    player1.gravity = 8;
    player1.veloY = 0;
    player1.burst_force = 400;

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
    for (int i = 0; i < NUM_FLOOR_BONES; i++) {
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

    // AI was used to help assist optimizing the bones and platforms into a single array
    // big bone
    bones[IDX_BIG_BONE].color = 0xFFFF;
    bones[IDX_BIG_BONE].length = BIG_BONE_HEIGHT;
    for (int i = 0; i < 3; i++) { bones[IDX_BIG_BONE].posx[i] = big_bone_x << 8; bones[IDX_BIG_BONE].posy[i] = big_bone_y << 8; }
    bones[IDX_BIG_BONE].velox = -LEVEL_SPEED * 1.1;
    bones[IDX_BIG_BONE].veloy = 0;

    // top bone 1
    bones[IDX_TOP_BONE].color = 0xFFFF;
    bones[IDX_TOP_BONE].length = 16;
    for (int i = 0; i < 3; i++) { bones[IDX_TOP_BONE].posx[i] = top_bone_x << 8; bones[IDX_TOP_BONE].posy[i] = top_bone_y << 8; }
    bones[IDX_TOP_BONE].velox = -LEVEL_SPEED * 1.1;
    bones[IDX_TOP_BONE].veloy = 0;

    // top bone 2
    bones[IDX_TOP_BONE2].color = 0xFFFF;
    bones[IDX_TOP_BONE2].length = 18;
    for (int i = 0; i < 3; i++) { bones[IDX_TOP_BONE2].posx[i] = top_bone2_x << 8; bones[IDX_TOP_BONE2].posy[i] = top_bone2_y << 8; }
    bones[IDX_TOP_BONE2].velox = -LEVEL_SPEED * 1.1;
    bones[IDX_TOP_BONE2].veloy = 0;

    // top bone 3
    bones[IDX_TOP_BONE3].color = 0xFFFF;
    bones[IDX_TOP_BONE3].length = 9;
    for (int i = 0; i < 3; i++) { bones[IDX_TOP_BONE3].posx[i] = top_bone3_x << 8; bones[IDX_TOP_BONE3].posy[i] = top_bone3_y << 8; }
    bones[IDX_TOP_BONE3].velox = -LEVEL_SPEED * 1.1;
    bones[IDX_TOP_BONE3].veloy = 0;

    // fast left bone
    bones[IDX_ENTRY_LEFT].color = 0xFFFF;
    bones[IDX_ENTRY_LEFT].length = 45;
    for (int i = 0; i < 3; i++) { bones[IDX_ENTRY_LEFT].posx[i] = (left_border - BONE_WIDTH) << 8; bones[IDX_ENTRY_LEFT].posy[i] = 129 << 8; }
    bones[IDX_ENTRY_LEFT].velox = 0;
    bones[IDX_ENTRY_LEFT].veloy = 0;

    // fast right bone
    bones[IDX_ENTRY_RIGHT].color = 0xFFFF;
    bones[IDX_ENTRY_RIGHT].length = 45;
    for (int i = 0; i < 3; i++) { bones[IDX_ENTRY_RIGHT].posx[i] = right_border << 8; bones[IDX_ENTRY_RIGHT].posy[i] = 142 << 8; }
    bones[IDX_ENTRY_RIGHT].velox = 0;
    bones[IDX_ENTRY_RIGHT].veloy = 0;

    // platform 1
    platforms[0].width = PLATFORM_WIDTH;
    platforms[0].height = PLATFORM_HEIGHT;
    platforms[0].posx[0] = first_platform_x << 8;
    platforms[0].posx[1] = first_platform_x << 8;
    platforms[0].posx[2] = first_platform_x << 8;
    platforms[0].posy[0] = platform_y << 8;
    platforms[0].posy[1] = platform_y << 8;
    platforms[0].posy[2] = platform_y << 8;
    platforms[0].velox = -LEVEL_SPEED * 1.1;
    platforms[0].veloy = 0;

    // platform 2
    platforms[1].width = PLATFORM_WIDTH;
    platforms[1].height = PLATFORM_HEIGHT;
    platforms[1].posx[0] = second_platform_x << 8;
    platforms[1].posx[1] = second_platform_x << 8;
    platforms[1].posx[2] = second_platform_x << 8;
    platforms[1].posy[0] = platform_y << 8;
    platforms[1].posy[1] = platform_y << 8;
    platforms[1].posy[2] = platform_y << 8;
    platforms[1].velox = -LEVEL_SPEED * 1.1;
    platforms[1].veloy = 0;

    // platform 3
    platforms[2].width = PLATFORM_WIDTH;
    platforms[2].height = PLATFORM_HEIGHT;
    platforms[2].posx[0] = third_platform_x << 8;
    platforms[2].posx[1] = third_platform_x << 8;
    platforms[2].posx[2] = third_platform_x << 8;
    platforms[2].posy[0] = third_platform_y << 8;
    platforms[2].posy[1] = third_platform_y << 8;
    platforms[2].posy[2] = third_platform_y << 8;
    platforms[2].velox = -LEVEL_SPEED * 1.1;
    platforms[2].veloy = 0;

    // platform 4
    platforms[3].width = PLATFORM_WIDTH;
    platforms[3].height = PLATFORM_HEIGHT;
    platforms[3].posx[0] = fourth_platform_x << 8;
    platforms[3].posx[1] = fourth_platform_x << 8;
    platforms[3].posx[2] = fourth_platform_x << 8;
    platforms[3].posy[0] = fourth_platform_y << 8;
    platforms[3].posy[1] = fourth_platform_y << 8;
    platforms[3].posy[2] = fourth_platform_y << 8;
    platforms[3].velox = -LEVEL_SPEED * 1.1;
    platforms[3].veloy = 0;

    // platform 5
    platforms[4].width = PLATFORM_WIDTH;
    platforms[4].height = PLATFORM_HEIGHT;
    platforms[4].posx[0] = fifth_platform_x << 8;
    platforms[4].posx[1] = fifth_platform_x << 8;
    platforms[4].posx[2] = fifth_platform_x << 8;
    platforms[4].posy[0] = fifth_platform_y << 8;
    platforms[4].posy[1] = fifth_platform_y << 8;
    platforms[4].posy[2] = fifth_platform_y << 8;
    platforms[4].velox = -LEVEL_SPEED * 1.1;
    platforms[4].veloy = 0;

    // platform 6
    platforms[5].width = SIXTH_PLATFORM_WIDTH;
    platforms[5].height = PLATFORM_HEIGHT;
    platforms[5].posx[0] = sixth_platform_x << 8;
    platforms[5].posx[1] = sixth_platform_x << 8;
    platforms[5].posx[2] = sixth_platform_x << 8;
    platforms[5].posy[0] = sixth_platform_y << 8;
    platforms[5].posy[1] = sixth_platform_y << 8;
    platforms[5].posy[2] = sixth_platform_y << 8;
    platforms[5].velox = -(LEVEL_SPEED * 0.71);
    platforms[5].veloy = 0;

    // should have been platfrom 2 whoops
    platforms[IDX_BIG_PLAT].width = PLATFORM_WIDTH;
    platforms[IDX_BIG_PLAT].height = PLATFORM_HEIGHT;
    for (int i = 0; i < 3; i++) { platforms[IDX_BIG_PLAT].posx[i] = big_platform_x << 8; platforms[IDX_BIG_PLAT].posy[i] = big_platform_y << 8; }
    platforms[IDX_BIG_PLAT].velox = -LEVEL_SPEED * 1.1;
    platforms[IDX_BIG_PLAT].veloy = 0;

    while (1) {
        draw_sans(&sans, bounds_unlimited);
        draw_head(&head, bounds_unlimited);
        for (int i = 0; i < NUM_BONES; i++) {
            draw_bone(&bones[i], 1, 0x0000, bounds_default);
        }
        for (int i = 0; i < NUM_PLATFORMS; i++) {
            erase_platform(&platforms[i], 1, bounds_default);
        }
		
		draw_player(&player1, 1, 0x0000);

        for (int i = 0; i < NUM_FLOOR_BONES; i++) {
            update_pos(bones[i].posx[0] + bones[i].velox, bones[i].posx);
            draw_bone(&bones[i], 0, 0xFFFF, bounds_default);
        }

        // when the two fast bones should come in based on the position of the smaller platform
        if (!entry_triggered && (platforms[5].posx[0] >> 8) <= 160) {
            bones[IDX_ENTRY_LEFT].velox = 1.5 * LEVEL_SPEED;
            bones[IDX_ENTRY_RIGHT].velox = -1.75 * LEVEL_SPEED;
            entry_triggered = 1;
        }

        for (int i = IDX_BIG_BONE; i < NUM_BONES; i++) {
            update_pos(bones[i].posx[0] + bones[i].velox, bones[i].posx);
            draw_bone(&bones[i], 0, 0xFFFF, bounds_default);
        }

        for (int i = 0; i < NUM_PLATFORMS; i++) {
            update_platform(&platforms[i]);
            draw_platform(&platforms[i], 0, bounds_default);
        }
		
		movement(&player1, &platforms, 7);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);
        if (player1.health == 0) {return 1;}

        swap_buffers();

        if (bones[NUM_FLOOR_BONES - 1].posx[0] <= ((left_border - 20) << 8)) {
            break;
        }
    }
	
	// interstage part

    *Global_health = player1.health;

    for (int i = 0; i< 4; i++) {
        player1.bounds[i] = bounds_unlimited[i];
    }

    clear_screen();
    swap_buffers();
    clear_screen();

    update_pos(160 << 8, player1.posx);
    update_pos(120 << 8, player1.posy);

    while (1) {

        draw_player(&player1, 1, 0x0000);
        int result = interstage_movement(&player1);
        draw_player(&player1, 0, 0xf800);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);

        draw_fight_button(100, 180);
        draw_iteam_button(200, 180);

        if (result == 2) {
            animate_sans_and_head(&sans, &head, bounds_unlimited);
            animate_attack(4, 161, 83, bounds_unlimited);
            return 2; // player chooses to fight
        } else if (result == 3) {
            *Global_health += 99;
            if (*Global_health > 99) {*Global_health = 99;}
            return 3; // player chooses to heal
        }

        swap_buffers();
    }
}
