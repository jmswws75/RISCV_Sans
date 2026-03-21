#include "graphics.h"
#include <math.h>

int subStageCount = 0;

void run_stage_0() {

    int bounds_unlimited[4] = {0, 0, 360, 240};
    int bounds_default[4] = {123, 116, 199, 192};

    graphics_init();

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
        swap_buffers();
        frameCount++;
    }

    frameCount = 0; // reset frameCount

    // substage0
    while (1) {
        if (frameCount > 9) {
            break;
        }

        draw_rectangle_outline(124, 166, 198, 191, 0xf800);
        swap_buffers();
        frameCount++;
    }

    frameCount = 0;
    draw_rectangle_outline(124, 166, 198, 191, 0x0000);
    swap_buffers();
    draw_rectangle_outline(124, 166, 198, 191, 0x0000);

    // substage1
    struct Bone bone_army_1[20];
    for (int i = 0; i < 20; i++) {
        bone_army_1[i].posx[0] = 199 - 7 * i << 8;
        bone_army_1[i].posx[1] = 199 - 7 * i << 8;
        bone_army_1[i].posx[2] = 199 - 7 * i << 8;
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
            draw_bone(bone_army_1[i].posx[1] >> 8, bone_army_1[i].posy[1] >> 8, bone_army_1[i].length,0x0000, bounds_default); //erase old one
        }

        for (int i = 0; i < 20; i++) {
            if(bone_army_1[i].posy[0] <= 166 << 8) {
                bone_army_1[i].veloy = 0;
            } else {
                update_pos(bone_army_1[i].posy[0] + bone_army_1[i].veloy, bone_army_1[i].posy); 
            }
            draw_bone(bone_army_1[i].posx[0] >> 8, bone_army_1[i].posy[0] >> 8, bone_army_1[i].length,0xFFFF, bounds_default); //draw new one
        }

        swap_buffers();
        frameCount++;

    }

    // erase all bones from substage1
    for (int i = 0; i < 20; i++) {
        draw_bone(bone_army_1[i].posx[0] >> 8, bone_army_1[i].posy[0] >> 8, bone_army_1[i].length,0x0000, bounds_default); //erase old one
    }
    swap_buffers();
    for (int i = 0; i < 20; i++) {
        draw_bone(bone_army_1[i].posx[0] >> 8, bone_army_1[i].posy[0] >> 8, bone_army_1[i].length,0x0000, bounds_default); //erase old one
    }
    swap_buffers();

    struct Bone bone_army[40];

    // loop to create the bones for the sin wave intro attack.
    // gap between top bone and bottom bone is 38/2 = 19 pixels
    for (int i = 0; i < 20; i++) {

		int sinValue = sin( (double)i / 3) * 20;
		
        bone_army[i].posx[0] = 60 - 14 * i << 8;
        bone_army[i].posx[1] = 60 - 14 * i << 8;
        bone_army[i].posx[2] = 60 - 14 * i << 8;
        bone_army[i].posy[0] = 117 << 8;
        bone_army[i].posy[1] = 117 << 8;
        bone_army[i].posy[2] = 117 << 8;
        bone_army[i].length = 20 + sinValue;
        bone_army[i].velox = 512;
        bone_army[i].veloy = 0;
        bone_army[i].color = 0xFFFF;

        int posy = 117 + (int)(41 + sinValue) << 8;

        bone_army[i+20].posx[0] = 60 - 14 * i << 8;
        bone_army[i+20].posx[1] = 60 - 14 * i << 8;
        bone_army[i+20].posx[2] = 60 - 14 * i << 8;
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
            draw_bone(bone_army[i].posx[1] >> 8, bone_army[i].posy[1] >> 8, bone_army[i].length,0x0000, bounds_default); //erase old one
        }

        for (int i = 0; i < 40; i++) {
            if(bone_army[i].posx[0] >= 210 << 8) {
                update_pos(-300 << 8, bone_army[i].posx);
            } else {
                update_pos(bone_army[i].posx[0] + bone_army[i].velox, bone_army[i].posx); 
            }
            draw_bone(bone_army[i].posx[0] >> 8, bone_army[i].posy[0] >> 8, bone_army[i].length,0xFFFF, bounds_default); //draw new one
        }

        swap_buffers();

    }
}