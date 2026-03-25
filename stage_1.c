#include "graphics.h"
#include "movement.h"
#include <math.h>
#include <stdbool.h>

void run_stage_1() {

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 360, 240};

    graphics_init();

    struct player player1;
    player1.fall_speed = 128;
    player1.rise_speed = 128;
    player1.ground = (192 - 8) << 8;
    player1.max_height = 30 << 8;
    for (int i = 0; i < 3; i++) {
        player1.posx[i] = 10 << 8;
        player1.posy[i] = 120 << 8;
    }
    player1.start_y = 0;
    player1.was_up_pressed = false;
    player1.force_fall = false;
    for (int i = 0; i< 4; i++) {
        player1.bounds[i] = bounds_default[i];
    }
    player1.have_gravity = true;
    player1.health = 99;

    while (1){

        draw_rectangle(67, 126, 254, 128, 0xFFFF, bounds_unlimited);
        draw_rectangle(67, 126, 69, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(67, 193, 254, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(252, 126, 254, 195, 0xFFFF, bounds_unlimited);
        
        draw_rectangle(70, 129, 251, 192, 0xffff, bounds_unlimited);


        movement(&player1);
        draw_player(&player1, 2, 0x0000);

        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health%10);
        draw_number(12,0,player1.health/10);
        draw_player(&player1, 0, 0xf800);

        draw_player(&player1, 0, 0xf800);

	    swap_buffers();
    }
    
}