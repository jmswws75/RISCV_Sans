#include "graphics.h"
#include <stdlib.h>
#include <stdbool.h>
#include "movement.h"

void swap_buffers(void);

#define PLATFORMS_PER_ROW 20
#define NUM_PLATFORMS (PLATFORMS_PER_ROW * 2)
#define PLATFORM_WIDTH 26
#define PLATFORM_HEIGHT 4
#define PLATFORM_GAP 54
#define LEVEL_SPEED 256
#define TOTAL_BLASTERS 10
#define BLASTER_SHOOT_RIGHT 270
#define BLASTER_SHOOT_LEFT 90
#define BLASTER_OFFSET 40

int run_stage_9(int *Global_health) {
    struct platform plats[NUM_PLATFORMS];
    struct blaster active_blaster;

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 319, 239};
	
	struct player player1;
    player1.ground = (192 - 5) << 8;
    for (int i = 0; i < 3; i++) {
        player1.posx[i] = 157 << 8;
        player1.posy[i] = 150 << 8;
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
    
    const int left_border = bounds_default[0];
    const int top_border = bounds_default[1];
    const int right_border = bounds_default[2];
    const int bottom_border = bounds_default[3];
    const int platform_step = PLATFORM_WIDTH + PLATFORM_GAP;
    const int bottom_row_y = bottom_border - 17 - PLATFORM_HEIGHT;
    const int top_row_y = bottom_row_y - 16 - PLATFORM_HEIGHT;
    const int bottom_row_start_x = right_border + 20;
    const int top_row_start_x = left_border - 20 - PLATFORM_WIDTH;
    const int section_centers[3] = {(top_border + (top_row_y - 1)) / 2, ((top_row_y + PLATFORM_HEIGHT) + (bottom_row_y - 1)) / 2, ((bottom_row_y + PLATFORM_HEIGHT) + (bottom_border - 1)) / 2};

    clear_screen();
    draw_rectangle(67, 126, 254, 128, 0xFFFF, bounds_unlimited);
    draw_rectangle(67, 126, 69, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(67, 193, 254, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(252, 126, 254, 195, 0xFFFF, bounds_unlimited);
    swap_buffers();
    clear_screen();
    draw_rectangle(67, 126, 254, 128, 0xFFFF, bounds_unlimited);
    draw_rectangle(67, 126, 69, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(67, 193, 254, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(252, 126, 254, 195, 0xFFFF, bounds_unlimited);
    swap_buffers();

    for (int i = 0; i < PLATFORMS_PER_ROW; i++) {
        int x = bottom_row_start_x + i * platform_step;
        plats[i].width = PLATFORM_WIDTH;
        plats[i].height = PLATFORM_HEIGHT;
        plats[i].posx[0] = x << 8;
        plats[i].posx[1] = x << 8;
        plats[i].posx[2] = x << 8;
        plats[i].posy[0] = bottom_row_y << 8;
        plats[i].posy[1] = bottom_row_y << 8;
        plats[i].posy[2] = bottom_row_y << 8;
        plats[i].velox = -LEVEL_SPEED;
        plats[i].veloy = 0;
    }

    for (int i = 0; i < PLATFORMS_PER_ROW; i++) {
        int idx = PLATFORMS_PER_ROW + i;
        int x = top_row_start_x - i * platform_step;
        plats[idx].width = PLATFORM_WIDTH;
        plats[idx].height = PLATFORM_HEIGHT;
        plats[idx].posx[0] = x << 8;
        plats[idx].posx[1] = x << 8;
        plats[idx].posx[2] = x << 8;
        plats[idx].posy[0] = top_row_y << 8;
        plats[idx].posy[1] = top_row_y << 8;
        plats[idx].posy[2] = top_row_y << 8;
        plats[idx].velox = LEVEL_SPEED;
        plats[idx].veloy = 0;
    }

    int blasters_spawned = 0;
    bool blaster_active = false;
    bool blaster_just_finished = false;

    while (1) {
		for (int i = 0; i < NUM_PLATFORMS; i++) {
			erase_platform(&plats[i], 2, bounds_default);
		}
		
		draw_player(&player1, 1, 0x0000);
		
        for (int i = 0; i < NUM_PLATFORMS; i++) {
            update_platform(&plats[i]);
            draw_platform(&plats[i], 0, bounds_default);
        }

        // only spawn blaster if previous one finished and haven't reached 10 blasters spawns yet
        if (!blaster_active && !blaster_just_finished && blasters_spawned < TOTAL_BLASTERS) {
            int spawn_from_left = (blasters_spawned % 2 == 0);
            int section = rand() % 3;   // 0 = top, 1 = middle, 2 = bottom
            active_blaster.centerx = spawn_from_left ? (left_border - BLASTER_OFFSET) : (right_border + BLASTER_OFFSET);
            active_blaster.centery = section_centers[section];
            active_blaster.size = 1;
            active_blaster.rotation = spawn_from_left ? BLASTER_SHOOT_RIGHT : BLASTER_SHOOT_LEFT;
            active_blaster.frameCount = 0;
            blaster_active = true;
        }

        // is the blaster finished and the count
        if (blaster_active) {
            draw_any_blaster(&active_blaster, bounds_unlimited);
            if (active_blaster.frameCount > 148) {
                blaster_active = false;
                blaster_just_finished = true;
                blasters_spawned++;
            }
        } else if (blaster_just_finished) {
            // erase ghost on the other buffer: wipe head area and beam area
            draw_rectangle(active_blaster.centerx - 20, active_blaster.centery - 20,
                           active_blaster.centerx + 20, active_blaster.centery + 20,
                           0x0000, bounds_unlimited);
            for (int j = active_blaster.beam_min_y; j < active_blaster.beam_max_y; j++) {
                draw_rectangle(active_blaster.beam_min_x[j], j,
                               active_blaster.beam_max_x[j], j,
                               0x0000, bounds_unlimited);
            }
            blaster_just_finished = false;
        }

        // redrawing the box cus blasters will eat it
        draw_rectangle(67, 126, 254, 128, 0xFFFF, bounds_unlimited);
        draw_rectangle(67, 126, 69, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(67, 193, 254, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(252, 126, 254, 195, 0xFFFF, bounds_unlimited);
		
		movement(&player1, &plats, NUM_PLATFORMS);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);
        if (player1.health == 0) {return 1;}

        swap_buffers();

        // end once 10 blasters spawn
        if (!blaster_active && blasters_spawned >= TOTAL_BLASTERS) {
            break;
        }
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
