// #include <stdbool.h>
// #include <stdlib.h>
// #include "graphics.h"

// #define PS2_BASE 0xFF200100

// volatile int *PS2_ptr = (int *)PS2_BASE;
// int bounds_unlimited[4] = {0, 0, 360, 240};

// void draw_player(int x, int y, short int color)
// {
//     draw_rectangle(x, y, x + 1, y + 1, color, bounds_unlimited);
// }

// void movement()
// {

//     int x[3], y[3];
//     for (int i = 0; i < 3) {
//         x[i] = 10;
//         y[i] = 120;
//     }

//     int PS2_data;
//     int RVALID;
//     unsigned char byte;

//     bool break_code = false;
//     bool up_pressed = false;
//     bool left_pressed = false;
//     bool down_pressed = false;
//     bool right_pressed = false;

//     int move_delay = 0;

//     clear_screen();
//     draw_player(x, y, 0xFFFF);

//     while (1) {
//         old_x = x;
//         old_y = y;

//         while (1) {
//             PS2_data = *PS2_ptr;
//             RVALID = PS2_data & 0x8000;
//             if (!RVALID)
//                 break;

//             byte = PS2_data & 0xFF;

//             if (byte == 0xE0) {
//                 continue;
//             } else if (byte == 0xF0) {
//                 break_code = true;
//                 continue;
//             }

//             if (byte == 0x1D) {          // W
//                 up_pressed = !break_code;
//             } else if (byte == 0x1C) {   // A
//                 left_pressed = !break_code;
//             } else if (byte == 0x1B) {   // S
//                 down_pressed = !break_code;
//             } else if (byte == 0x23) {   // D
//                 right_pressed = !break_code;
//             }

//             break_code = false;
//         }

//         move_delay++;
//         if (move_delay > 50000) {
//             move_delay = 0;

// 			// Second condition is the boundary
//             if (up_pressed && y > 0) y--;
//             if (left_pressed && x > 0) x--;
//             if (down_pressed && y < 234) y++;
//             if (right_pressed && x < 314) x++;
//         }

//         if (x != old_x || y != old_y) {
//             draw_player(old_x, old_y, 0x0000);
//             draw_player(x, y, 0xFFFF);
//         }
//     }
// }