#include "graphics.h"
#include "movement.h"
#include <stdlib.h>

#define BONE_WIDTH 5
#define BONE_SPACING 35
#define BOTTOM_BONE_HEIGHT 6
#define TOP_BONE_HEIGHT 42
#define LEVEL_SPEED 512

int run_stage_19(int *Global_health) {
    struct Bone left_bones[7];
    struct Bone right_bones[7];

    int bounds_default[4] = {123, 116, 199, 192};
    int bounds_unlimited[4] = {0, 0, 319, 239};
	
	graphics_init();
    
	struct player player1;
    player1.ground = (192 - 5) << 8;
    for (int i = 0; i < 3; i++) {
        player1.posx[i] = 157 << 8;
        player1.posy[i] = 150 << 8;
    }
    player1.was_up_pressed = false;
    player1.have_gravity = false;
    
    for (int i = 0; i< 4; i++) {
        player1.bounds[i] = bounds_default[i];
    }
    player1.health = *Global_health;
    player1.gravity = 8;
    player1.veloY = 0;
    player1.burst_force = 400;
	
	clear_screen();
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
	
	for (int i = 0; i < 7; i++) {
		left_bones[i].color = 0xFFFF;
        left_bones[i].length = 92;
        left_bones[i].posx[0] = 65 << 8;
        left_bones[i].posx[1] = 65 << 8;
        left_bones[i].posx[2] = 65 << 8;
        left_bones[i].posy[0] = (-80 * i) << 8;
        left_bones[i].posy[1] = (-80 * i) << 8;
        left_bones[i].posy[2] = (-80 * i) << 8;
        left_bones[i].velox = 0;
        left_bones[i].veloy = LEVEL_SPEED;
	}
	
	for (int i = 0; i < 7; i++) {
		right_bones[i].color = 0xFFFF;
        right_bones[i].length = 92;
        right_bones[i].posx[0] = 165 << 8;
        right_bones[i].posx[1] = 165 << 8;
        right_bones[i].posx[2] = 165 << 8;
        right_bones[i].posy[0] = 240 + (80 * i) << 8;
        right_bones[i].posy[1] = 240+ (80 * i) << 8;
        right_bones[i].posy[2] = 240+ (80 * i) << 8;
        right_bones[i].velox = 0;
        right_bones[i].veloy = -LEVEL_SPEED;
	}
	
    int frame_count = 0;
	
    while (1) {

        for (int i = 0; i < 7; i++) {
			draw_bone_h(&left_bones[i], 1, 0x0000, bounds_unlimited);
		}
		
		for (int i = 0; i < 7; i++) {
			draw_bone_h(&right_bones[i], 1, 0x0000, bounds_unlimited);
		}
		
		draw_player(&player1, 1, 0x0000);
		
		draw_rectangle(120, 113, 202, 115, 0xFFFF, bounds_unlimited);
		draw_rectangle(120, 113, 122, 195, 0xFFFF, bounds_unlimited);
		draw_rectangle(120, 193, 202, 195, 0xFFFF, bounds_unlimited);
		draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);
		
		for (int i = 0; i < 7; i++) {
            update_pos(left_bones[i].posy[0] + left_bones[i].veloy, left_bones[i].posy);
            draw_bone_h(&left_bones[i], 0, 0xFFFF, bounds_unlimited);
        }
		
		for (int i = 0; i < 7; i++) {
            update_pos(right_bones[i].posy[0] + right_bones[i].veloy, right_bones[i].posy);
            draw_bone_h(&right_bones[i], 0, 0xFFFF, bounds_unlimited);
        }
		
		movement(&player1, NULL, 0);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);
        if (player1.health == 0) {return 1;}
		
        swap_buffers();

        // stop condition
        
		frame_count++;
		
		if (frame_count >= 400) {break;}
		
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