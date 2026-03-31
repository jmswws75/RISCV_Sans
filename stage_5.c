#include <stdbool.h>
#include "graphics.h"
#include <stdlib.h>
#include "movement.h"

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

int run_stage_5(int *Global_health) {
    struct Bone bones[NUM_BONES];
    struct Bone top_fast[NUM_FAST_BONES];
    struct platform plats[NUM_PLATFORMS];
    struct Bone end_bone;

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 319, 239};

    struct player player1;
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

    const int bone_draw_width = 5;
    const int bone_step = bone_draw_width + BONE_SPACING;

    const int first_bone_x = left_border - (NUM_BONES * bone_step) - 30;
    const int bone_y = 176;

    const int platform_y = bone_y - PLATFORM_GAP - PLATFORM_HEIGHT;
    const int first_platform_x = left_border - 243 - 30;

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

        draw_player(&player1, 1, 0x0000);

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
        
        movement(&player1, &plats, NUM_PLATFORMS);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);
        if (player1.health == 0) {return 1;}

        for (int i = 0; i < NUM_PLATFORMS; i++) {
            update_platform(&plats[i]);
            draw_platform(&plats[i], 0, bounds_default);
        }

        swap_buffers();

        if (end_bone.posx[0] > (320 << 8)) {
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
            return 2; // player chooses to fight
        } else if (result == 3) {
            *Global_health += 99;
            if (*Global_health > 99) {*Global_health = 99;}
            return 3; // player chooses to heal
        }

        swap_buffers();
    }
}
