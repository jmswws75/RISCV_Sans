#include "graphics.h"
#include "movement.h"
#include <math.h>
#include <stdlib.h>

int run_stage_13(int *Global_health) {

    int bounds_unlimited[4] = {0, 0, 360, 240};
    int bounds_default[4] = {63, 141, 260, 192};

    graphics_init();

    struct player player1;
    player1.ground = (192 - 5) << 8;
    for (int i = 0; i < 3; i++) {
        player1.posx[i] = 160 << 8;
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

    struct Bone Bone_army[6];

    for (int i = 0; i < 6; i++) {
        Bone_army[i].color = 0xffff;
        Bone_army[i].veloy = 0;
        if (i < 3) {Bone_army[i].velox = -600;}
        else {Bone_army[i].velox = 600;}
    }

    // right
    Bone_army[0].posx[0] = 270 << 8;
    Bone_army[0].posx[1] = 270 << 8;
    Bone_army[0].posx[2] = 270 << 8;
    Bone_army[0].posy[0] = 142 << 8;
    Bone_army[0].posy[1] = 142 << 8;
    Bone_army[0].posy[2] = 142 << 8;
    Bone_army[0].length = 38;

    Bone_army[1].posx[0] = (270 + 48) << 8;
    Bone_army[1].posx[1] = (270 + 48) << 8;
    Bone_army[1].posx[2] = (270 + 48) << 8;
    Bone_army[1].posy[0] = 181 << 8;
    Bone_army[1].posy[1] = 181 << 8;
    Bone_army[1].posy[2] = 181 << 8;
    Bone_army[1].length = 5;

    Bone_army[2].posx[0] = (270 + 48 + 12) << 8;
    Bone_army[2].posx[1] = (270 + 48 + 12) << 8;
    Bone_army[2].posx[2] = (270 + 48 + 12) << 8;
    Bone_army[2].posy[0] = 142 << 8;
    Bone_army[2].posy[1] = 142 << 8;
    Bone_army[2].posy[2] = 142 << 8;
    Bone_army[2].length = 44;

    // left
    Bone_army[3].posx[0] = 53 << 8;
    Bone_army[3].posx[1] = 53 << 8;
    Bone_army[3].posx[2] = 53 << 8;
    Bone_army[3].posy[0] = 142 << 8;
    Bone_army[3].posy[1] = 142 << 8;
    Bone_army[3].posy[2] = 142 << 8;
    Bone_army[3].length = 38;

    Bone_army[4].posx[0] = (53 - 48) << 8;
    Bone_army[4].posx[1] = (53 - 48) << 8;
    Bone_army[4].posx[2] = (53 - 48) << 8;
    Bone_army[4].posy[0] = 181 << 8;
    Bone_army[4].posy[1] = 181 << 8;
    Bone_army[4].posy[2] = 181 << 8;
    Bone_army[4].length = 5;

    Bone_army[5].posx[0] = (53 - 48 - 12) << 8;
    Bone_army[5].posx[1] = (53 - 48 - 12) << 8;
    Bone_army[5].posx[2] = (53 - 48 - 12) << 8;
    Bone_army[5].posy[0] = 142 << 8;
    Bone_army[5].posy[1] = 142 << 8;
    Bone_army[5].posy[2] = 142 << 8;
    Bone_army[5].length = 44;

    draw_rectangle(60, 138, 263, 140, 0xFFFF, bounds_unlimited);
    draw_rectangle(60, 138, 62, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(261, 138, 263, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(60, 193, 263, 195, 0xFFFF, bounds_unlimited);

    swap_buffers();

    draw_rectangle(60, 138, 263, 140, 0xFFFF, bounds_unlimited);
    draw_rectangle(60, 138, 62, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(261, 138, 263, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(60, 193, 263, 195, 0xFFFF, bounds_unlimited);

    swap_buffers();

    int frameCount = 0;

    while (1) {

        if (frameCount > 67){ break; }

        for (int i = 0; i < 6; i++) {
            draw_bone(&Bone_army[i], 1, 0x0000, bounds_default);
        }

        draw_player(&player1, 1, 0x0000);

        for (int i = 0; i < 6; i++) {
            update_pos(Bone_army[i].posx[0] + Bone_army[i].velox, Bone_army[i].posx);
            draw_bone(&Bone_army[i], 0, 0xFFFF, bounds_default);
        }
        
		if (player1.health == 0) {return 1;}
		
        movement(&player1, NULL, 0);
        draw_player(&player1, 0, 0xf800);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);

        draw_rectangle(60, 138, 263, 140, 0xFFFF, bounds_unlimited);
        draw_rectangle(60, 138, 62, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(261, 138, 263, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(60, 193, 263, 195, 0xFFFF, bounds_unlimited);
        
        swap_buffers();
        frameCount++;
    }

    *Global_health = player1.health;

}