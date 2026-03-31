#include <stdbool.h>
#include "graphics.h"
#include "movement.h"

#define NUM_BOTTOM_BONES 40
#define NUM_VERT_BONES   20
#define NUM_VERT_LAYERS  3

#define BOTTOM_BONE_HEIGHT 7
#define BOTTOM_BONE_GAP    5

#define VERTICAL_BONE_HEIGHT 12
#define VERTICAL_BONE_GAP    50
#define VERTICAL_LAYER_GAP   37
#define LEFT_WALL_GAP        83

#define PLATFORM_WIDTH  21
#define PLATFORM_HEIGHT 4

#define LEVEL_SPEED 192

int run_stage_8(int *Global_health) {
    struct Bone bottom_bones[NUM_BOTTOM_BONES];
    struct Bone vertical_bones[NUM_VERT_LAYERS][NUM_VERT_BONES];
    struct platform plat;

    int bounds_default[4] = {62, 121, 268, 189};
    int bounds_unlimited[4] = {0, 0, 319, 239};
	
	const int left_border = bounds_default[0];
    const int top_border = bounds_default[1];
    const int right_border = bounds_default[2];
    const int bottom_border = bounds_default[3];

    const int bone_width = 5;

    const int bottom_step = bone_width + BOTTOM_BONE_GAP;
    const int bottom_y = bottom_border - BOTTOM_BONE_HEIGHT - 5;

    const int platform_start_x = left_border + 12;
    const int platform_right_limit = right_border - PLATFORM_WIDTH - 8;
    const int platform_y = 170;

    const int layer_x_0 = left_border + LEFT_WALL_GAP;
    const int layer_x_1 = layer_x_0 + VERTICAL_LAYER_GAP;
    const int layer_x_2 = layer_x_0 + (2 * VERTICAL_LAYER_GAP);
	
	struct player player1;
    player1.ground = (192 - 5) << 8;
    for (int i = 0; i < 3; i++) {
        player1.posx[i] = platform_start_x + 12 << 8;
        player1.posy[i] = 160 << 8;
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

    clear_screen();
    draw_rectangle(59, 118, 271, 120, 0xFFFF, bounds_unlimited);
    draw_rectangle(59, 118, 61, 192, 0xFFFF, bounds_unlimited);
    draw_rectangle(59, 193, 271, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(269, 118, 271, 192, 0xFFFF, bounds_unlimited);
    swap_buffers();

    clear_screen();
    draw_rectangle(59, 118, 271, 120, 0xFFFF, bounds_unlimited);
    draw_rectangle(59, 118, 61, 192, 0xFFFF, bounds_unlimited);
    draw_rectangle(59, 193, 271, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(269, 118, 271, 192, 0xFFFF, bounds_unlimited);
    swap_buffers();

    // bottom bones
    for (int i = 0; i < NUM_BOTTOM_BONES; i++) {
        int x = right_border - (i * bottom_step);
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

    // platform
    plat.width = PLATFORM_WIDTH;
    plat.height = PLATFORM_HEIGHT;
    plat.posx[0] = platform_start_x << 8;
    plat.posx[1] = platform_start_x << 8;
    plat.posx[2] = platform_start_x << 8;
    plat.posy[0] = platform_y << 8;
    plat.posy[1] = platform_y << 8;
    plat.posy[2] = platform_y << 8;
    plat.velox = LEVEL_SPEED;
    plat.veloy = 0;

    // vertical bone layer 1
    for (int i = 0; i < NUM_VERT_BONES; i++) {
        int y = top_border + i * VERTICAL_BONE_GAP;
        vertical_bones[0][i].color = 0xFFFF;
        vertical_bones[0][i].length = VERTICAL_BONE_HEIGHT;
        vertical_bones[0][i].posx[0] = layer_x_0 << 8;
        vertical_bones[0][i].posx[1] = layer_x_0 << 8;
        vertical_bones[0][i].posx[2] = layer_x_0 << 8;
        vertical_bones[0][i].posy[0] = y << 8;
        vertical_bones[0][i].posy[1] = y << 8;
        vertical_bones[0][i].posy[2] = y << 8;
        vertical_bones[0][i].velox = 0;
        vertical_bones[0][i].veloy = -LEVEL_SPEED;
    }

    // veritcal bone layer 2
    for (int i = 0; i < NUM_VERT_BONES; i++) {
        int y = bottom_border - i * VERTICAL_BONE_GAP;
        vertical_bones[1][i].color = 0xFFFF;
        vertical_bones[1][i].length = VERTICAL_BONE_HEIGHT;
        vertical_bones[1][i].posx[0] = layer_x_1 << 8;
        vertical_bones[1][i].posx[1] = layer_x_1 << 8;
        vertical_bones[1][i].posx[2] = layer_x_1 << 8;
        vertical_bones[1][i].posy[0] = y << 8;
        vertical_bones[1][i].posy[1] = y << 8;
        vertical_bones[1][i].posy[2] = y << 8;
        vertical_bones[1][i].velox = 0;
        vertical_bones[1][i].veloy = LEVEL_SPEED;
    }

    // vertical bone layer 3
    for (int i = 0; i < NUM_VERT_BONES; i++) {
        int y = top_border + i * VERTICAL_BONE_GAP + 15;
        vertical_bones[2][i].color = 0xFFFF;
        vertical_bones[2][i].length = VERTICAL_BONE_HEIGHT;
        vertical_bones[2][i].posx[0] = layer_x_2 << 8;
        vertical_bones[2][i].posx[1] = layer_x_2 << 8;
        vertical_bones[2][i].posx[2] = layer_x_2 << 8;
        vertical_bones[2][i].posy[0] = y << 8;
        vertical_bones[2][i].posy[1] = y << 8;
        vertical_bones[2][i].posy[2] = y << 8;
        vertical_bones[2][i].velox = 0;
        vertical_bones[2][i].veloy = -LEVEL_SPEED;
    }

    int turned_once = 0;

    while (1) {
        // erase the bottom bones
        for (int i = 0; i < NUM_BOTTOM_BONES; i++) {
            draw_bone(&bottom_bones[i], 1, 0x0000, bounds_default);
        }
        erase_platform(&plat, 1, bounds_default);

        // get rid of the vertical bones
        draw_rectangle(layer_x_0, top_border, layer_x_0 + 4, bottom_border, 0x0000, bounds_default);
        draw_rectangle(layer_x_1, top_border, layer_x_1 + 4, bottom_border, 0x0000, bounds_default);
        draw_rectangle(layer_x_2, top_border, layer_x_2 + 4, bottom_border, 0x0000, bounds_default);

		draw_player(&player1, 1, 0x0000);

        // update and draw the bottom bones
        for (int i = 0; i < NUM_BOTTOM_BONES; i++) {
            update_pos(bottom_bones[i].posx[0] + bottom_bones[i].velox, bottom_bones[i].posx);
            if ((bottom_bones[i].posx[0] >> 8) > right_border + bone_width) {
                int new_x = (bottom_bones[i].posx[0] >> 8) - (NUM_BOTTOM_BONES * bottom_step);
                update_pos(new_x << 8, bottom_bones[i].posx);
            }
            draw_bone(&bottom_bones[i], 0, 0xFFFF, bounds_default);
        }

        // update and draw the vertical bones
        for (int i = 0; i < NUM_VERT_BONES; i++) {
            update_pos(vertical_bones[0][i].posy[0] + vertical_bones[0][i].veloy,
                       vertical_bones[0][i].posy);
            draw_bone(&vertical_bones[0][i], 0, 0xFFFF, bounds_default);

            update_pos(vertical_bones[1][i].posy[0] + vertical_bones[1][i].veloy,
                       vertical_bones[1][i].posy);
            draw_bone(&vertical_bones[1][i], 0, 0xFFFF, bounds_default);

            update_pos(vertical_bones[2][i].posy[0] + vertical_bones[2][i].veloy,
                       vertical_bones[2][i].posy);
            draw_bone(&vertical_bones[2][i], 0, 0xFFFF, bounds_default);
        }

        // ending stage condition
        update_platform(&plat);
        if (!turned_once && ((plat.posx[0] >> 8) >= platform_right_limit)) {
            plat.velox = -LEVEL_SPEED;
            turned_once = 1;
        }
        draw_platform(&plat, 0, bounds_default);

		movement(&player1, &plat, 1);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);
        if (player1.health == 0) {return 1;}

        swap_buffers();

        if (turned_once && ((plat.posx[0] >> 8) <= platform_start_x)) {
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
