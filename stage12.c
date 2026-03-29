#include "graphics.h"
#include "movement.h"
#include <math.h>
#include <stdlib.h>

int run_stage_12(int *Global_health) {

    int bounds_unlimited[4] = {0, 0, 360, 240};
    int bounds_default[4] = {123, 116, 199, 192};

    graphics_init();

    struct player player1;
    player1.ground = (192 - 5) << 8;
    for (int i = 0; i < 3; i++) {
        player1.posx[i] = 50 << 8;
        player1.posy[i] = player1.ground << 8;
    }
    player1.was_up_pressed = false;
    player1.have_gravity = true;
    
    for (int i = 0; i< 4; i++) {
        player1.bounds[i] = bounds_default[i];
    }
    player1.health = *Global_health;
    player1.gravity = 16;
    player1.veloY = 0;
    player1.burst_force = 500;

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

    int frameCount = 0;

    struct blaster blaster_army_1[4];
	blaster_army_1[0].centerx = 94;
    blaster_army_1[0].centery = 156;
	blaster_army_1[0].rotation = 270;
    blaster_army_1[0].frameCount = 0;
	
    blaster_army_1[1].centerx = 226;
    blaster_army_1[1].centery = 156;
	blaster_army_1[1].rotation = 90;
    blaster_army_1[1].frameCount = 0;
	
    blaster_army_1[2].centerx = 159;
    blaster_army_1[2].centery = 92;
	blaster_army_1[2].rotation = 0;
    blaster_army_1[2].frameCount = 0;
	
    blaster_army_1[3].centerx = 159;
    blaster_army_1[3].centery = 218;
	blaster_army_1[3].rotation = 180;
    blaster_army_1[3].frameCount = 0;

    while (1) {

        if (frameCount > 800){ break; }

        draw_player(&player1, 1, 0x0000);
        
        
		if (player1.health == 0) {return 1;}

 		for (int i = 0; i < 4; i++) {
			draw_any_blaster(&blaster_army_1[i], bounds_unlimited);
		}
		
        movement(&player1, NULL, 0);
        draw_player(&player1, 0, 0xf800);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);

        draw_rectangle(120, 113, 202, 115, 0xFFFF, bounds_unlimited);
        draw_rectangle(120, 113, 122, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(120, 193, 202, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);

        
        swap_buffers();
        frameCount++;
    }

}