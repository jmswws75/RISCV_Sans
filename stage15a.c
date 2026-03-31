#include "graphics.h"
#include <stdlib.h>
#include "movement.h"

#define NUM_SETS 5
#define TOTAL_BONES 20

#define GAP_SIZE 16
#define START_Y 129
#define BOTTOM_LIMIT 186
#define SET_SPACING 120

int run_stage_15a(int *Global_health) {
    struct Bone Bone_army[TOTAL_BONES];

    int bounds_default[4] = {92, 116, 199, 192};
    int bounds_unlimited[4] = {0, 0, 319, 239};
	
	graphics_init();

    struct player player1;
    player1.ground = (192 - 5) << 8;
    for (int i = 0; i < 3; i++) {
        player1.posx[i] = 157 << 8;
        player1.posy[i] = 130 << 8;
    }
    player1.was_up_pressed = false;
    player1.have_gravity = false;
    
    for (int i = 0; i< 4; i++) {
        player1.bounds[i] = bounds_default[i];
    }
    player1.health = *Global_health;
    player1.gravity = 8;
    player1.veloY = 0;
    player1.burst_force = 512;

    int left_border = bounds_default[0];
    int right_border = bounds_default[2];

    clear_screen();

    draw_rectangle(89, 113, 202, 115, 0xFFFF, bounds_unlimited);
    draw_rectangle(89, 113, 91, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(89, 193, 202, 195, 0xFFFF, bounds_unlimited);
    swap_buffers();

    clear_screen();

    draw_rectangle(89, 113, 202, 115, 0xFFFF, bounds_unlimited);
    draw_rectangle(89, 113, 91, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(89, 193, 202, 195, 0xFFFF, bounds_unlimited);
    swap_buffers();

    // substage 2: sin wave
    struct Bone bone_army[40];

    // loop to create the bones for the sin wave intro attack.
    // gap between top bone and bottom bone is 38/2 = 19 pixels
    for (int i = 0; i < 20; i++) {

		int sinValue = sin( (i - 4.5) / 2.8 ) * 16;
		
        bone_army[i].posx[0] = (60 - 14 * i) << 8;
        bone_army[i].posx[1] = (60 - 14 * i) << 8;
        bone_army[i].posx[2] = (60 - 14 * i) << 8;
        bone_army[i].posy[0] = 117 << 8;
        bone_army[i].posy[1] = 117 << 8;
        bone_army[i].posy[2] = 117 << 8;
        bone_army[i].length = 20 + sinValue;
        bone_army[i].velox = 512;
        bone_army[i].veloy = 0;
        bone_army[i].color = 0xFFFF;

        int posy = 117 + (int)(41 + sinValue) << 8;

        bone_army[i+20].posx[0] = (60 - 14 * i) << 8;
        bone_army[i+20].posx[1] = (60 - 14 * i) << 8;
        bone_army[i+20].posx[2] = (60 - 14 * i) << 8;
        bone_army[i+20].posy[0] = posy;
        bone_army[i+20].posy[1] = posy;
        bone_army[i+20].posy[2] = posy;
        bone_army[i+20].length = 186 - (posy >> 8);
        bone_army[i+20].velox = 512;
        bone_army[i+20].veloy = 0;
        bone_army[i+20].color = 0xFFFF;
    }
	
	int frame_count = 0;

    while (1) {
        
        for (int i = 0; i < 40; i++) {
            draw_bone(&bone_army[i], 1, 0x0000, bounds_default); //erase old one
        }

        draw_player(&player1, 1, 0x0000);

        for (int i = 0; i < 40; i++) {
            update_pos(bone_army[i].posx[0] + bone_army[i].velox, bone_army[i].posx); 
            draw_bone(&bone_army[i], 0, 0xffff, bounds_default); //draw new one
        }
        
        movement(&player1, NULL, 0);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);
        // if (player1.health == 0) {return 1;}

        swap_buffers();
		
		frame_count++;

        if (frame_count >= 240){
			break;
        }

    }

    *Global_health = player1.health;
	
}