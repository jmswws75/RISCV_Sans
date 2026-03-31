/*
TODO: 
revamp gravity
make collision logic for platforms.
*/

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

    draw_rectangle(x, y, x + 5, y + 5, color, bounds_unlimited);

    
}

void movement(struct player *player_ptr, struct platform *platforms_ptr, int numPlatforms){

    int PS2_data;
    int RVALID;
    unsigned char byte;

    int velox = 400;
    int veloy = 400;

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

        if (byte == 0x1D) {  // W
            up_pressed = !break_code;
        } else if (byte == 0x1C) {  // A
            left_pressed = !break_code;
        } else if (byte == 0x23) {  // D
            right_pressed = !break_code;
        } else if (byte == 0x1B) {  // S
            down_pressed = !break_code;
        }

        break_code = false;
    }

    int newX = player_ptr->posx[0];
    int newY = player_ptr->posy[0];

    int playerX = player_ptr->posx[0] >> 8;
    int playerY = player_ptr->posy[0] >> 8;
    int size = 5;
    int sizeIn8 = 5 << 8;

    if (player_ptr->have_gravity) {

        bool isGrounded = false;
        int oldY = player_ptr->posy[1];
        player_ptr->veloY += player_ptr->gravity; // default gravity increase

        newY += player_ptr->veloY;

        if (newY >= player_ptr->ground) {
            newY = player_ptr->ground;
            player_ptr->veloY = 0;
            isGrounded = true;
        }

        //platform logic
        for (int i = 0; i < numPlatforms; i++) { // loop thru every platform
            int platXstart = platforms_ptr[i].posx[0]; // putting these here to make it clean
            int platXend = platforms_ptr[i].posx[0] + (platforms_ptr[i].width << 8);
            int platYtop = platforms_ptr[i].posy[0];
            if (newX + sizeIn8 >= platXstart && newX <= platXend && player_ptr->veloY > 0 && oldY + sizeIn8 <= platYtop && newY + sizeIn8 >= platYtop) {
                newY = platYtop - sizeIn8;
                player_ptr->veloY = 0;
                isGrounded = true;
                newX += platforms_ptr[i].velox;
            }
        }

        if (up_pressed && !player_ptr->was_up_pressed && isGrounded) { // apply initial bust force
            player_ptr->veloY = -player_ptr->burst_force; 
        }
        if (!up_pressed && player_ptr->veloY < 0) { // release w
            player_ptr->veloY = player_ptr->veloY / 2;
        }

        // x direction movement
        if (left_pressed && newX > 0)
            newX-=velox;
        if (right_pressed && newX < PLAYER_MAX_X)
            newX+=velox;

    }

    else { // no gravity
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
    if (newX > (player_ptr->bounds[2] - 5) << 8) newX = (player_ptr->bounds[2] - 5) << 8;

    bool overlap = false;
    if (read_pixel(playerX, playerY) == 0xffff) {overlap = true;}
    if (read_pixel(playerX + size, playerY) == 0xffff) {overlap = true;}
    if (read_pixel(playerX, playerY + size) == 0xffff) {overlap = true;}
    if (read_pixel(playerX + size, playerY + size) == 0xffff) {overlap = true;}
    if (read_pixel(playerX + size/2, playerY + size/2) == 0xffff) {overlap = true;}

    if (overlap && player_ptr->health > 0) {player_ptr->health--;}

    player_ptr->was_up_pressed = up_pressed;
    
    update_pos(newX, player_ptr->posx);
    update_pos(newY, player_ptr->posy);

}

int interstage_movement(struct player *player_ptr) {
    int PS2_data;
    int RVALID;
    unsigned char byte;

    int velox = 400;
    int veloy = 400;

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

    if (left_pressed && newX > 0)
        newX-=velox;
    if (right_pressed && newX < PLAYER_MAX_X) {
        newX+=velox;
    }
    if (up_pressed) {newY -= veloy;}
    if (down_pressed) {newY += veloy;}

    // Guarantee that the player stays on the screen (CAN MODIFY THIS FOR THE ACTUAL GAME)
    if (newY < (player_ptr->bounds[1]) << 8) newY = player_ptr->bounds[1] << 8;
    if (newY > (player_ptr->ground)) newY = player_ptr->ground;
    if (newX < (player_ptr->bounds[0]) << 8) newX = (player_ptr->bounds[0]) << 8;
    if (newX > (player_ptr->bounds[2] - 5) << 8) newX = (player_ptr->bounds[2] - 5) << 8;

    int playerX = player_ptr->posx[0] >> 8;
    int playerY = player_ptr->posy[0] >> 8;
    int size = 7;

    bool overlap_heal = false;
    bool overlap_fight = false;
    if (read_pixel(playerX, playerY) == 0xfb85) {overlap_fight = true;}
    if (read_pixel(playerX + size, playerY) == 0xfb85) {overlap_fight = true;}
    if (read_pixel(playerX, playerY + size) == 0xfb85) {overlap_fight = true;}
    if (read_pixel(playerX + size, playerY + size) == 0xfb85) {overlap_fight = true;}
    if (read_pixel(playerX + size/2, playerY + size/2) == 0xfb85) {overlap_fight = true;}

    if (read_pixel(playerX, playerY) == 0xbdd7) {overlap_heal = true;}
    if (read_pixel(playerX + size, playerY) == 0xbdd7) {overlap_heal = true;}
    if (read_pixel(playerX, playerY + size) == 0xbdd7) {overlap_heal = true;}
    if (read_pixel(playerX + size, playerY + size) == 0xbdd7) {overlap_heal = true;}
    if (read_pixel(playerX + size/2, playerY + size/2) == 0xbdd7) {overlap_heal = true;}

    update_pos(newX, player_ptr->posx);
    update_pos(newY, player_ptr->posy);

    if (overlap_fight) {
		break_code = false;
		up_pressed = false;
		left_pressed = false;
		right_pressed = false;
		down_pressed = false;
        return 2;
    } else if (overlap_heal) {
		break_code = false;
		up_pressed = false;
		left_pressed = false;
		right_pressed = false;
		down_pressed = false;
        return 3;
    } else { return 0; }

}

int start_check() {
    int PS2_data;
    int RVALID;
    unsigned char byte;

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

    if (left_pressed) {
        return 1;
    } else {return 0;}
}
