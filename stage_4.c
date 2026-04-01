#include "graphics.h"
#include <stdlib.h>
#include "movement.h"

#define NUM_SETS 5
#define TOTAL_BONES 20

#define GAP_SIZE 16
#define START_Y 129
#define BOTTOM_LIMIT 186
#define SET_SPACING 120

// change the top length of the bone to be between 10 and 33
static int random_top_length(int previous_top_len) {
    int top_len = 10 + (rand() % 24);

    // if it is too close to the previous length redo the random length
    while (previous_top_len >= 0 && abs(top_len - previous_top_len) < 6) {
        top_len = 10 + (rand() % 24);
    }

    return top_len;
}

int run_stage_4(int *Global_health) {
    struct Bone Bone_army[TOTAL_BONES];

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 319, 239};

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
    player1.burst_force = 512;

    int left_border = bounds_default[0];
    int right_border = bounds_default[2];

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

    int prev_top = -1;  // remember the previous top bone height (to make sure that the next random one isn't too similar)

    for (int g = 0; g < NUM_SETS; g++) {
        int r = 2 * g;          // indcies (0,2,4,6,8)
        int l = 10 + 2 * g;     // indicies (10,12,14,16,18)

        // places the bones off the screen starting x positions
        int base_x_r = right_border + 30 + g * SET_SPACING;
        int base_x_l = left_border - 30 - g * SET_SPACING;

        // make obstacle height
        int top_len = random_top_length(prev_top);
        prev_top = top_len;

        // calculate where bottom bone starts
        int bottom_y = START_Y + top_len + GAP_SIZE;

        int bot_len = BOTTOM_LIMIT - bottom_y;

        // prevent bottom bone from becoming too small
        if (bot_len < 4) {
            bot_len = 4;
            bottom_y = BOTTOM_LIMIT - bot_len;
        }

        // right top
        Bone_army[r].color = 0xFFFF;
        Bone_army[r].length = top_len;
        Bone_army[r].posx[0] = base_x_r << 8;
        Bone_army[r].posx[1] = base_x_r << 8;
        Bone_army[r].posx[2] = base_x_r << 8;
        Bone_army[r].posy[0] = START_Y << 8;
        Bone_army[r].posy[1] = START_Y << 8;
        Bone_army[r].posy[2] = START_Y << 8;
        Bone_army[r].velox = -384;
        Bone_army[r].veloy = 0;

        // right bottom
        Bone_army[r + 1].color = 0xFFFF;
        Bone_army[r + 1].length = bot_len;
        Bone_army[r + 1].posx[0] = base_x_r << 8;
        Bone_army[r + 1].posx[1] = base_x_r << 8;
        Bone_army[r + 1].posx[2] = base_x_r << 8;
        Bone_army[r + 1].posy[0] = bottom_y << 8;
        Bone_army[r + 1].posy[1] = bottom_y << 8;
        Bone_army[r + 1].posy[2] = bottom_y << 8;
        Bone_army[r + 1].velox = -384;
        Bone_army[r + 1].veloy = 0;

        // left top
        Bone_army[l].color = 0xFFFF;
        Bone_army[l].length = top_len;
        Bone_army[l].posx[0] = base_x_l << 8;
        Bone_army[l].posx[1] = base_x_l << 8;
        Bone_army[l].posx[2] = base_x_l << 8;
        Bone_army[l].posy[0] = START_Y << 8;
        Bone_army[l].posy[1] = START_Y << 8;
        Bone_army[l].posy[2] = START_Y << 8;
        Bone_army[l].velox = 384;
        Bone_army[l].veloy = 0;

        // left bottom
        Bone_army[l + 1].color = 0xFFFF;
        Bone_army[l + 1].length = bot_len;
        Bone_army[l + 1].posx[0] = base_x_l << 8;
        Bone_army[l + 1].posx[1] = base_x_l << 8;
        Bone_army[l + 1].posx[2] = base_x_l << 8;
        Bone_army[l + 1].posy[0] = bottom_y << 8;
        Bone_army[l + 1].posy[1] = bottom_y << 8;
        Bone_army[l + 1].posy[2] = bottom_y << 8;
        Bone_army[l + 1].velox = 384;
        Bone_army[l + 1].veloy = 0;
    }

    while (1) {
        draw_sans(&sans, bounds_unlimited);
        draw_head(&head, bounds_unlimited);
        for (int i = 0; i < TOTAL_BONES; i++) {
            draw_bone(&Bone_army[i], 1, 0x0000, bounds_default);
        }

        draw_player(&player1, 1, 0x0000);

        for (int i = 0; i < TOTAL_BONES; i++) {
            update_pos(Bone_army[i].posx[0] + Bone_army[i].velox, Bone_army[i].posx);
            draw_bone(&Bone_army[i], 0, 0xFFFF, bounds_default);
        }

        movement(&player1, NULL, 0);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);
        if (player1.health == 0) {return 1;}

        swap_buffers();

        if (Bone_army[9].posx[0] <= ((left_border - 20) << 8) &&
            Bone_army[18].posx[0] >= ((right_border + 20) << 8)) {
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
