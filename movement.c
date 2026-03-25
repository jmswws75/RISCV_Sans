#include "graphics.h"
#include "movement.h"
#include <stdbool.h>
#include <stdlib.h>

#define PS2_BASE 0xFF200100
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

volatile int *PS2_ptr = (int *)PS2_BASE;

// Functions from graphics.c
void graphics_init(void);
void swap_buffers(void);

// Player size (MAKE SURE TO CHANGE THIS FOR ACTUAL GAME)
#define PLAYER_SIZE 8
// Player bounds
#define PLAYER_MAX_X ((SCREEN_WIDTH - PLAYER_SIZE) << 8)

void draw_player(struct player *player_ptr, short int ind, short int color)
{
    int bounds_unlimited[4] = {0, 0, 360, 240};

    int x = player_ptr->posx[ind] >> 8;
    int y = player_ptr->posy[ind] >> 8;

    draw_rectangle(x, y, x + 7, y + 7, color, bounds_unlimited);

    
}

void movement(struct player *player_ptr){

    int PS2_data;
    int RVALID;
    unsigned char byte;

    static bool break_code = false;
    static bool up_pressed = false;
    static bool left_pressed = false;
    static bool right_pressed = false;
    static bool down_pressed = false;

    int velox = 128;
    int veloy = 128;

	// Gravity state
    

    // Read everything in buffer
    while (1) {
        PS2_data = *PS2_ptr;
        RVALID = PS2_data & 0x8000;
        if (!RVALID){
            break;
        }

        byte = PS2_data & 0xFF;

        if (byte == 0xE0) {
            continue;
        } else if (byte == 0xF0) {
            break_code = true;
            continue;
        }

        if (byte == 0x1D) {          // W
            up_pressed = !break_code;
        } else if (byte == 0x1C) {   // A
            left_pressed = !break_code;
        } else if (byte == 0x23) {   // D
            right_pressed = !break_code;
        } else if (byte == 0x1B) {   // S
            down_pressed = !break_code;
        }

        break_code = false;
    }

    int newX = player_ptr->posx[0];
    int newY = player_ptr->posy[0];

    if (player_ptr->have_gravity) {
        if (left_pressed && newX > 0)
            newX-=velox;
        if (right_pressed && newX < PLAYER_MAX_X)
            newX+=velox;
        // Detect start of upward hold
        if (up_pressed && !player_ptr->was_up_pressed && !player_ptr->force_fall && newY >= player_ptr->ground) {
            player_ptr->start_y = newY;
        }

        if (!up_pressed && newY < player_ptr->ground) {
            player_ptr->force_fall = true;
        }

        // Force fall logic
        if (player_ptr->force_fall) {
            if (newY < player_ptr->ground) {
                newY += player_ptr->fall_speed;
            } else {
                newY = player_ptr->ground;
                player_ptr->force_fall = false;
            }
        // Rising logic
        } else if (up_pressed) {
            if (newY > 0 && newY > player_ptr->start_y - player_ptr->max_height) {	// Check if gone too high (aka within range of jumping)
                newY -= player_ptr->rise_speed;
            } else {
                player_ptr->force_fall = true;
            }
        // Normal falling
        } else {
            if (newY < player_ptr->ground) {
                newY += player_ptr->fall_speed;
            }
        }
    }

    else {
        if (left_pressed && newX > 0)
            newX-=velox;
        if (right_pressed && newX < PLAYER_MAX_X) {
            newX+=velox;
        }
        if (up_pressed) {newY -= veloy;}
        if (down_pressed) {newY += veloy;}
    }
    

    // Guarantee that the player stays on the screen (CAN MODIFY THIS FOR THE ACTUAL GAME)
    if (newY < (player_ptr->bounds[1]) << 8) newY = player_ptr->bounds[1] << 8;
    if (newY > (player_ptr->ground)) newY = player_ptr->ground;
    if (newX < (player_ptr->bounds[0]) << 8) newX = (player_ptr->bounds[0]) << 8;
    if (newX > (player_ptr->bounds[2] - 8) << 8) newX = (player_ptr->bounds[2] - 8) << 8;

    if (read_pixel(player_ptr->posx[0], player_ptr->posy[0]) == 0xffff) {
        player_ptr->health--;
    }

    player_ptr->was_up_pressed = up_pressed;
    
    update_pos(newX, player_ptr->posx);
    update_pos(newY, player_ptr->posy);

}