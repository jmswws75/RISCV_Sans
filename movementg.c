#include "graphics.h"
#include <stdbool.h>
#include <stdlib.h>

#define PS2_BASE 0xFF200100
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

volatile int *PS2_ptr = (int *)PS2_BASE;

// Functions from graphics.c
void graphics_init(void);
void swap_buffers(void);
extern int bounds_unlimited[4];

// Player size (MAKE SURE TO CHANGE THIS FOR ACTUAL GAME)
#define PLAYER_SIZE 2
// Player bounds
#define PLAYER_MAX_X (SCREEN_WIDTH - PLAYER_SIZE)
#define PLAYER_MAX_Y 234

void draw_player(int x, int y, short int color)
{
    draw_rectangle(x, y, x + 1, y + 1, color, bounds_unlimited);
}

int main(void)
{
    int x = 10, y = 120;

    int PS2_data;
    int RVALID;
    unsigned char byte;

    bool break_code = false;
    bool up_pressed = false;
    bool left_pressed = false;
    bool right_pressed = false;

    int move_delay = 0;

    const int rise_speed = 1;
    const int fall_speed = 1;
    const int ground = PLAYER_MAX_Y;
    const int max_height = 30;

	// Gravity state
    int start_y = 0;
    bool was_up_pressed = false;
    bool force_fall = false;

    graphics_init();	// Initialize graphics

    while (1) {
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
            }

            break_code = false;
        }

        if (left_pressed && x > 0)
            x--;
        if (right_pressed && x < PLAYER_MAX_X)
            x++;
		// Detect start of upward hold
        if (up_pressed && !was_up_pressed && !force_fall) {
            start_y = y;
        }

		// Force fall logic
        if (force_fall) {
            if (y < ground) {
                y += fall_speed;
            } else {
                y = ground;
                force_fall = false;
            }
		// Rising logic
        } else if (up_pressed) {
            if (y > 0 && y > start_y - max_height) {	// Check if gone too high (aka within range of jumping)
                y -= rise_speed;
            } else {
                force_fall = true;
            }
		// Normal falling
        } else {
            if (y < ground) {
                y += fall_speed;
            }
        }

		// Guarantee that the player stays on the screen (CAN MODIFY THIS FOR THE ACTUAL GAME)
        if (y < 0) y = 0;
        if (y > ground) y = ground;

        was_up_pressed = up_pressed;
        
        clear_screen();
        draw_player(x, y, 0xFFFF);
        swap_buffers();
    }

    return 0;
}