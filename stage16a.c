#include "graphics.h"
#include <stdlib.h>
#include "movement.h"

#define NUM_SETS 5
#define TOTAL_BONES 20

#define GAP_SIZE 16
#define START_Y 129
#define BOTTOM_LIMIT 186
#define SET_SPACING 120

int run_stage_16a(int *Global_health) {

    int bounds_unlimited[4] = {0, 0, 360, 240};
    int bounds_default[4] = {63, 141, 260, 192};
	
	graphics_init();

    struct player player1;
    player1.ground = (192 - 5) << 8;
    for (int i = 0; i < 3; i++) {
        player1.posx[i] = 255 << 8;
        player1.posy[i] = 187 << 8;
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

    int left_border = bounds_default[0];
    int right_border = bounds_default[2];

    clear_screen();

    draw_rectangle(60, 138, 263, 140, 0xFFFF, bounds_unlimited);
    draw_rectangle(60, 138, 62, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(261, 138, 263, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(60, 193, 263, 195, 0xFFFF, bounds_unlimited);
    swap_buffers();

    clear_screen();

    draw_rectangle(60, 138, 263, 140, 0xFFFF, bounds_unlimited);
    draw_rectangle(60, 138, 62, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(261, 138, 263, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(60, 193, 263, 195, 0xFFFF, bounds_unlimited);
    swap_buffers();

    struct Bone bone_army[21];

    for (int i = 0; i < 21; i++) {
		
		if (i < 11){
			bone_army[i].posx[0] = (20 - 14 * i) << 8;
			bone_army[i].posx[1] = (20 - 14 * i) << 8;
			bone_army[i].posx[2] = (20 - 14 * i) << 8;
			bone_army[i].posy[0] = 166 << 8;
			bone_army[i].posy[1] = 166 << 8;
			bone_army[i].posy[2] = 166 << 8;
			bone_army[i].length = 20;
			bone_army[i].velox = 900;
			bone_army[i].veloy = 0;
			bone_army[i].color = 0xFFFF;
		} else {
			bone_army[i].posx[0] = (20 - 14 * i) << 8;
			bone_army[i].posx[1] = (20 - 14 * i) << 8;
			bone_army[i].posx[2] = (20 - 14 * i) << 8;
			bone_army[i].posy[0] = 181 << 8;
			bone_army[i].posy[1] = 181 << 8;
			bone_army[i].posy[2] = 181 << 8;
			bone_army[i].length = 5;
			bone_army[i].velox = 900;
			bone_army[i].veloy = 0;
			bone_army[i].color = 0xFFFF;
		}
        

    }
	
	int frame_count = 0;

    while (1) {
        
        for (int i = 0; i < 21; i++) {
            draw_bone(&bone_army[i], 1, 0x0000, bounds_default); //erase old one
        }

        draw_player(&player1, 1, 0x0000);

        for (int i = 0; i < 21; i++) {
            update_pos(bone_army[i].posx[0] + bone_army[i].velox, bone_army[i].posx); 
            draw_bone(&bone_army[i], 0, 0xffff, bounds_default); //draw new one
        }
        
        movement(&player1, NULL, 0);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);
        if (player1.health == 0) {return 1;}

        swap_buffers();
		
		frame_count++;

        if (frame_count >= 160){
			break;
        }

    }

    *Global_health = player1.health;
	
}