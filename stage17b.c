#include "graphics.h"
#include <stdlib.h>
#include "movement.h"

#define NUM_SETS 5
#define TOTAL_BONES 20

#define GAP_SIZE 16
#define START_Y 129
#define BOTTOM_LIMIT 186
#define SET_SPACING 120

#define PLATFORM_WIDTH 20
#define PLATFORM_HEIGHT 4

int run_stage_17b(int *Global_health) {

    int bounds_unlimited[4] = {0, 0, 360, 240};
    int bounds_default[4] = {63, 141, 260, 192};
	
	graphics_init();

    struct player player1;
    player1.ground = (192 - 5) << 8;
    for (int i = 0; i < 3; i++) {
        player1.posx[i] = 161 << 8;
        player1.posy[i] = 152 << 8;
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

    struct Bone bone_army[31];
	struct Bone laundromat[2];
	struct platform plats[2];
	
	plats[0].width = PLATFORM_WIDTH;
	plats[0].height = PLATFORM_HEIGHT;
	plats[0].posx[0] = 155 << 8;
	plats[0].posx[1] = 155 << 8;
	plats[0].posx[2] = 155 << 8;
	plats[0].posy[0] = 157 << 8;
	plats[0].posy[1] = 157 << 8;
	plats[0].posy[2] = 157 << 8;
	plats[0].velox = 0;
	plats[0].veloy = 0;
	
	plats[1].width = PLATFORM_WIDTH;
	plats[1].height = PLATFORM_HEIGHT;
	plats[1].posx[0] = 155 << 8;
	plats[1].posx[1] = 155 << 8;
	plats[1].posx[2] = 155 << 8;
	plats[1].posy[0] = 177 << 8;
	plats[1].posy[1] = 177 << 8;
	plats[1].posy[2] = 177 << 8;
	plats[1].velox = 0;
	plats[1].veloy = 0;
	
	laundromat[0].posx[0] = (263) << 8;
	laundromat[0].posx[1] = (263) << 8;
	laundromat[0].posx[2] = (263) << 8;
	laundromat[0].posy[0] = 142 << 8;
	laundromat[0].posy[1] = 142 << 8;
	laundromat[0].posy[2] = 142 << 8;
	laundromat[0].length = 5;
	laundromat[0].velox = -512;
	laundromat[0].veloy = 0;
	laundromat[0].color = 0xFFFF;
	
	laundromat[1].posx[0] = (-5) << 8;
	laundromat[1].posx[1] = (-5) << 8;
	laundromat[1].posx[2] = (-5) << 8;
	laundromat[1].posy[0] = 160 << 8;
	laundromat[1].posy[1] = 160 << 8;
	laundromat[1].posy[2] = 160 << 8;
	laundromat[1].length = 30;
	laundromat[1].velox = 512;
	laundromat[1].veloy = 0;
	laundromat[1].color = 0xFFFF;

    for (int i = 0; i < 31; i++) {
		
		bone_army[i].posx[0] = (60 + 7 * i) << 8;
		bone_army[i].posx[1] = (60 + 7 * i) << 8;
		bone_army[i].posx[2] = (60 + 7 * i) << 8;
		bone_army[i].posy[0] = 185 << 8;
		bone_army[i].posy[1] = 185 << 8;
		bone_army[i].posy[2] = 185 << 8;
		bone_army[i].length = 20;
		bone_army[i].velox = 0;
		bone_army[i].veloy = 0;
		bone_army[i].color = 0xFFFF;
        

    }
	
	int frame_count = 0;

    while (1) {
        
		// bottom bone sea
        for (int i = 0; i < 31; i++) {
            draw_bone(&bone_army[i], 1, 0x0000, bounds_default); //erase old one
        }
		
		for (int i = 0; i < 2; i++) {
			draw_bone(&laundromat[i], 1, 0x0000, bounds_default); //erase old one
		}
		
		// platforms
		for (int i = 0; i < 2; i++) {
            erase_platform(&plats[i], 1, bounds_default);
        }

        draw_player(&player1, 1, 0x0000);

		// bottom bone sea
        for (int i = 0; i < 31; i++) {
            update_pos(bone_army[i].posx[0] + bone_army[i].velox, bone_army[i].posx); 
            draw_bone(&bone_army[i], 0, 0xffff, bounds_default); //draw new one
        }
		
		// swiper
        for (int i = 0; i < 2; i++) {
            update_pos(laundromat[i].posx[0] + laundromat[i].velox, laundromat[i].posx); 
            draw_bone(&laundromat[i], 0, 0xffff, bounds_default); //draw new one
        }
		
		// platforms
		for (int i = 0; i < 2; i++) {
            update_platform(&plats[i]);
            draw_platform(&plats[i], 0, bounds_default);
        }
        
        movement(&player1, &plats, 2);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
		draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);
        if (player1.health == 0) {return 1;}

        swap_buffers();
		
		frame_count++;

        if (frame_count >= 140){
			break;
        }

    }

	*Global_health = player1.health;
	
}