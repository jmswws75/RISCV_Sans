#include <math.h>
#include "graphics.h"
#include "movement.h"
#include <stdlib.h>

int run_stage_3(int *Global_health) {
    struct Bone Bone_army[12];

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 360, 240};

    struct player player1;
    struct Sans sans;
    sans.centerx = 161;
    sans.centery = 83;

    struct Head head;
    head.centerx = 161;
    head.centery = 83;
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

    int left_border  = bounds_default[0];   // 70
    int right_border = bounds_default[2];   // 251

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

    // Phase 1 from the right
    for (int g = 0; g < 3; g++) {
        int i = 2 * g;

        // each next set starts farther right so they enter one after another
        int base_x = right_border + 107 * (g + 0.5);
		
		// "blue" top
        Bone_army[i].color = 0xffff;
        Bone_army[i].length = 42;
        Bone_army[i].posx[0] = (base_x - 33) << 8;
        Bone_army[i].posx[1] = (base_x - 33) << 8;
        Bone_army[i].posx[2] = (base_x - 33) << 8;
        Bone_army[i].posy[0] = 129 << 8;
        Bone_army[i].posy[1] = 129 << 8;
        Bone_army[i].posy[2] = 129 << 8;
        Bone_army[i].velox = -512;
        Bone_army[i].veloy = 0;
		
        // white bottom
        Bone_army[i + 1].color = 0xffff;
        Bone_army[i + 1].length = 4;
        Bone_army[i + 1].posx[0] = base_x << 8;
        Bone_army[i + 1].posx[1] = base_x << 8;
        Bone_army[i + 1].posx[2] = base_x << 8;
        Bone_army[i + 1].posy[0] = 183 << 8;
        Bone_army[i + 1].posy[1] = 183 << 8;
        Bone_army[i + 1].posy[2] = 183 << 8;
        Bone_army[i + 1].velox = -512;
        Bone_army[i + 1].veloy = 0;
    }

    while (1) {
        draw_sans(&sans, bounds_unlimited);
        draw_head(&head, bounds_unlimited);
        for (int i = 0; i < 6; i++) {
            draw_bone(&Bone_army[i], 1, 0x0000, bounds_default);
        }

        draw_player(&player1, 1, 0x0000);

        for (int i = 0; i < 6; i++) {
            update_pos(Bone_army[i].posx[0] + Bone_army[i].velox, Bone_army[i].posx);
            draw_bone(&Bone_army[i], 0, 0xffff, bounds_default);
        }

        movement(&player1, NULL, 0);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);
        if (player1.health == 0) {return 1;}

        swap_buffers();

        if (Bone_army[5].posx[0] <= ((left_border - 20) << 8)) {
            break;
        }
    }

    // Phase 2 from the left
    for (int g = 0; g < 3; g++) {
        int i = 6 + 2 * g;

        // each next set starts farther left so they enter one after another
        int base_x = left_border - 107 * (g + 0.5);

		// "blue" top
        Bone_army[i].color = 0xffff;
        Bone_army[i].length = 42;
        Bone_army[i].posx[0] = (base_x + 33) << 8;
        Bone_army[i].posx[1] = (base_x + 33) << 8;
        Bone_army[i].posx[2] = (base_x + 33) << 8;
        Bone_army[i].posy[0] = 129 << 8;
        Bone_army[i].posy[1] = 129 << 8;
        Bone_army[i].posy[2] = 129 << 8;
        Bone_army[i].velox = 512;
        Bone_army[i].veloy = 0;
		
        // white bottom
        Bone_army[i + 1].color = 0xffff;
        Bone_army[i + 1].length = 4;
        Bone_army[i + 1].posx[0] = base_x << 8;
        Bone_army[i + 1].posx[1] = base_x << 8;
        Bone_army[i + 1].posx[2] = base_x << 8;
        Bone_army[i + 1].posy[0] = 183 << 8;
        Bone_army[i + 1].posy[1] = 183 << 8;
        Bone_army[i + 1].posy[2] = 183 << 8;
        Bone_army[i + 1].velox = 512;
        Bone_army[i + 1].veloy = 0;

        
    }

    while (1) {
        draw_sans(&sans, bounds_unlimited);
        draw_head(&head, bounds_unlimited);
        for (int i = 6; i < 12; i++) {
            draw_bone(&Bone_army[i], 1, 0x0000, bounds_default);
        }

        draw_player(&player1, 1, 0x0000);

        for (int i = 6; i < 12; i++) {
            update_pos(Bone_army[i].posx[0] + Bone_army[i].velox, Bone_army[i].posx);
            draw_bone(&Bone_army[i], 0, 0xffff, bounds_default);
        }

        movement(&player1, NULL, 0);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0x01de);
        if (player1.health == 0) {return 1;}

        swap_buffers();

        if (Bone_army[11].posx[0] >= ((right_border + 20) << 8)) {
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
        draw_sans(&sans, bounds_unlimited);
        draw_head(&head, bounds_unlimited);
        draw_player(&player1, 1, 0x0000);
        draw_sans(&sans, bounds_unlimited);
        draw_head(&head, bounds_unlimited);
        int result = interstage_movement(&player1);
        draw_player(&player1, 0, 0xf800);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_fight_button(100, 180);
        draw_iteam_button(200, 180);

        if (result == 2) {
            animate_sans_and_head(&sans, &head, bounds_unlimited);
            animate_attack(4, 161, 83, bounds_unlimited);
            return 2; // player chooses to fight
        } else if (result == 3) {
            *Global_health += 99;
            if (*Global_health > 99) {*Global_health = 99;}
            return 3; // player chooses to heal
        }

        swap_buffers();
    }
}
