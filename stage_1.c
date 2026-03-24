#include "graphics.h"
#include "movement.h"
#include <math.h>
#include <stdbool.h>

void run_stage_1() {
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

    while (1){

        draw_player(&player1, 1, 0x0000);

        movement(&player1);

        draw_player(&player1, 0, 0xf800);

	    swap_buffers();
    }
    
}