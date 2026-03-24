#include "graphics.h"
#include "movement.h"
#include <math.h>

int subStageCount = 0;

void run_stage_0() {

    int bounds_unlimited[4] = {0, 0, 360, 240};
    int bounds_default[4] = {123, 116, 199, 192};

    graphics_init();

    struct player player1;
    player1.fall_speed = 128;
    player1.rise_speed = 128;
    player1.ground = 226 << 8;
    player1.max_height = 30 << 8;
    for (int i = 0; i < 3; i++) {
        player1.posx[i] = 10 << 8;
        player1.posy[i] = 120 << 8;
    }
    player1.start_y = 0;
    player1.was_up_pressed = false;
    player1.force_fall = false;
    player1.have_gravity = false;

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

    
    // wait for half a sec
    int frameCount = 0;
    while (1) {
        if (frameCount > 30) {
            break;
        }

        draw_player(&player1, 1, 0x0000);
        movement(&player1);
        draw_player(&player1, 0, 0xf800);

        swap_buffers();
        frameCount++;
    }

    frameCount = 0; // reset frameCount

    // substage0: red lines
    while (1) {

        if (frameCount > 9) {
            break;
        }

        draw_player(&player1, 1, 0x0000);
        movement(&player1);
        draw_player(&player1, 0, 0xf800);

        draw_rectangle_outline(124, 166, 198, 191, 0xf800);
        swap_buffers();
        frameCount++;
    }

    frameCount = 0;
    draw_rectangle_outline(124, 166, 198, 191, 0x0000);
    swap_buffers();
    draw_rectangle_outline(124, 166, 198, 191, 0x0000);

    // substage1: bottom bone
    struct Bone bone_army_1[20];
    for (int i = 0; i < 20; i++) {
        bone_army_1[i].posx[0] = (199 - 7 * i) << 8;
        bone_army_1[i].posx[1] = (199 - 7 * i )<< 8;
        bone_army_1[i].posx[2] = (199 - 7 * i )<< 8;
        bone_army_1[i].posy[0] = 196 << 8;
        bone_army_1[i].posy[1] = 196 << 8;
        bone_army_1[i].posy[2] = 196 << 8;
        bone_army_1[i].length = 30;
        bone_army_1[i].velox = 0;
        bone_army_1[i].veloy = -512;
        bone_army_1[i].color = 0xFFFF;
    }

    while (1) {
        
        if (frameCount > 120) {
            break;
        }

        for (int i = 0; i < 20; i++) {
            draw_bone(&bone_army_1[i], 1, 0x0000, bounds_default); //erase old one
        }

        draw_player(&player1, 1, 0x0000);
        movement(&player1);
        

        for (int i = 0; i < 20; i++) {
            if(bone_army_1[i].posy[0] <= 166 << 8) {
                bone_army_1[i].veloy = 0;
            } else {
                update_pos(bone_army_1[i].posy[0] + bone_army_1[i].veloy, bone_army_1[i].posy); 
            }
            draw_bone(&bone_army_1[i], 0, 0xffff, bounds_default); //draw new one
        }

        draw_player(&player1, 0, 0xf800);

        swap_buffers();
        frameCount++;

    }

    // erase all bones from substage1
    for (int i = 0; i < 20; i++) {
		draw_bone(&bone_army_1[i], 0, 0x0000, bounds_default); //erase old one
		draw_bone(&bone_army_1[i], 1, 0x0000, bounds_default); //erase old one
        draw_bone(&bone_army_1[i], 2, 0x0000, bounds_default); //erase old one
    }
    swap_buffers();
    for (int i = 0; i < 20; i++) {
		draw_bone(&bone_army_1[i], 0, 0x0000, bounds_default); //erase old one
		draw_bone(&bone_army_1[i], 1, 0x0000, bounds_default); //erase old one
        draw_bone(&bone_army_1[i], 2, 0x0000, bounds_default); //erase old one
    }
    swap_buffers();


    // substage 2: sin wave
    struct Bone bone_army[40];

    // loop to create the bones for the sin wave intro attack.
    // gap between top bone and bottom bone is 38/2 = 19 pixels
    for (int i = 0; i < 20; i++) {

		int sinValue = sin( (double)i / 3) * 20;
		
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
        bone_army[i+20].length = 186- (posy >> 8);
        bone_army[i+20].velox = 512;
        bone_army[i+20].veloy = 0;
        bone_army[i+20].color = 0xFFFF;
    }

    while (1) {
        
        for (int i = 0; i < 40; i++) {
            draw_bone(&bone_army[i], 1, 0x0000, bounds_default); //erase old one
        }

        for (int i = 0; i < 40; i++) {
            update_pos(bone_army[i].posx[0] + bone_army[i].velox, bone_army[i].posx); 
            draw_bone(&bone_army[i], 0, 0xffff, bounds_default); //draw new one
        }

        if(bone_army[39].posx[0] >= 240 << 8) {
            break;
        }

        swap_buffers();

    }

    frameCount = 0;

    // substage 3: blasters
    struct blaster blaster_army_0[4];
    blaster_army_0[0].centerx = 135;
    blaster_army_0[0].centery = 70;
	blaster_army_0[0].rotation = 0;
    blaster_army_0[0].frameCount = 0;
	
    blaster_army_0[1].centerx = 80;
    blaster_army_0[1].centery = 128;
	blaster_army_0[1].rotation = 270;
    blaster_army_0[1].frameCount = 0;
	
    blaster_army_0[2].centerx = 187;
    blaster_army_0[2].centery = 225;
	blaster_army_0[2].rotation = 180;
    blaster_army_0[2].frameCount = 0;
	
    blaster_army_0[3].centerx = 235;
    blaster_army_0[3].centery = 181;
	blaster_army_0[3].rotation = 90;
    blaster_army_0[3].frameCount = 0;
    

    struct blaster blaster_army_1[4];
	blaster_army_1[0].centerx = 100;
    blaster_army_1[0].centery = 95;
	blaster_army_1[0].rotation = 315;
    blaster_army_1[0].frameCount = -200;
	
    blaster_army_1[1].centerx = 100;
    blaster_army_1[1].centery = 215;
	blaster_army_1[1].rotation = 225;
    blaster_army_1[1].frameCount = -200;
	
    blaster_army_1[2].centerx = 220;
    blaster_army_1[2].centery = 215;
	blaster_army_1[2].rotation = 135;
    blaster_army_1[2].frameCount = -200;
	
    blaster_army_1[3].centerx = 220;
    blaster_army_1[3].centery = 100;
	blaster_army_1[3].rotation = 45;
    blaster_army_1[3].frameCount = -200;
	
	
    struct blaster blaster_army_2[4];
	blaster_army_2[0].centerx = 135;
    blaster_army_2[0].centery = 70;
	blaster_army_2[0].rotation = 0;
    blaster_army_2[0].frameCount = -400;
	
    blaster_army_2[1].centerx = 80;
    blaster_army_2[1].centery = 128;
	blaster_army_2[1].rotation = 270;
    blaster_army_2[1].frameCount = -400;
	
    blaster_army_2[2].centerx = 187;
    blaster_army_2[2].centery = 225;
	blaster_army_2[2].rotation = 180;
    blaster_army_2[2].frameCount = -400;
	
    blaster_army_2[3].centerx = 235;
    blaster_army_2[3].centery = 181;
	blaster_army_2[3].rotation = 90;
    blaster_army_2[3].frameCount = -400;
	
    struct blaster blaster_army_3[2];
	blaster_army_3[0].centerx = 90;
    blaster_army_3[0].centery = 145;
	blaster_army_3[0].rotation = 270;
    blaster_army_3[0].frameCount = -600;
	
    blaster_army_3[1].centerx = 230;
    blaster_army_3[1].centery = 160;
	blaster_army_3[1].rotation = 90;
    blaster_army_3[1].frameCount = -600;

    while (1) {

        if (frameCount > 800){ break; }
		
 		for (int i = 0; i < 4; i++) {
			draw_any_blaster(&blaster_army_0[i], bounds_unlimited);
			draw_any_blaster(&blaster_army_1[i], bounds_unlimited);
			draw_any_blaster(&blaster_army_2[i], bounds_unlimited);
		}
		
		draw_any_blaster(&blaster_army_3[0], bounds_unlimited);
		draw_any_blaster(&blaster_army_3[1], bounds_unlimited);
		
        draw_rectangle(120, 113, 202, 115, 0xFFFF, bounds_unlimited);
        draw_rectangle(120, 113, 122, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(120, 193, 202, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);

        
        swap_buffers();
        frameCount++;
    }

}