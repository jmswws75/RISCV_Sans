#include <stdlib.h>

#define NUM_BONES_PER_ROW 8
#define NUM_ROWS 3
#define TOTAL_BONES (NUM_BONES_PER_ROW * NUM_ROWS)
#define PLATS_PER_LAYER 4
#define NUM_PLATFORMS (PLATS_PER_LAYER * 2)

#define BONE_LENGTH 15
#define MIN_BONE_GAP 30
#define MAX_BONE_GAP 60
#define BONE_DRAW_WIDTH 5

#define MIN_PLAT_WIDTH 50
#define MAX_PLAT_WIDTH 90
#define PLAT_HEIGHT 3
#define PLAT_GAP 20

#define LEVEL_SPEED 256

#define ROW_Y0 129
#define ROW_Y1 150 
#define ROW_Y2 171 

#define PLAT_LAYER0 148
#define PLAT_LAYER1 169 

void run_stage_7(void) {
    struct Bone bones[TOTAL_BONES];
    struct platform plats[NUM_PLATFORMS];

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 319, 239};

    const int left_border = bounds_default[0];
    const int right_border = bounds_default[2];

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

    int row_y[NUM_ROWS] = {ROW_Y0, ROW_Y1, ROW_Y2};

    // bone creation (AI was used here to optimize making the bones)
    for (int row = 0; row < NUM_ROWS; row++) {
        int goes_right = (row == 0 || row == 2);
        int x = goes_right ? (left_border - 30) : (right_border + 30);

        for (int i = 0; i < NUM_BONES_PER_ROW; i++) {
            int idx = row * NUM_BONES_PER_ROW + i;

            bones[idx].color = 0xFFFF;
            bones[idx].length = BONE_LENGTH;
            bones[idx].posx[0] = x << 8;
            bones[idx].posx[1] = x << 8;
            bones[idx].posx[2] = x << 8;
            bones[idx].posy[0] = row_y[row] << 8;
            bones[idx].posy[1] = row_y[row] << 8;
            bones[idx].posy[2] = row_y[row] << 8;
            bones[idx].velox = goes_right ? LEVEL_SPEED : -LEVEL_SPEED;
            bones[idx].veloy = 0;

            int gap = MIN_BONE_GAP + (rand() % (MAX_BONE_GAP - MIN_BONE_GAP + 1));
            if (goes_right)
                x -= BONE_DRAW_WIDTH + gap;
            else
                x += BONE_DRAW_WIDTH + gap;
        }
    }

    int plat_layer_y[2] = {PLAT_LAYER0, PLAT_LAYER1};

    // platform creation (AI was used here to optimize making the platforms)
    for (int layer = 0; layer < 2; layer++) {
        int goes_right = (layer == 0);
        int x = goes_right ? (left_border - 100) : (right_border + 100);

        for (int i = 0; i < PLATS_PER_LAYER; i++) {
            int idx = layer * PLATS_PER_LAYER + i;
            int w = MIN_PLAT_WIDTH + (rand() % (MAX_PLAT_WIDTH - MIN_PLAT_WIDTH + 1));

            plats[idx].width = w;
            plats[idx].height = PLAT_HEIGHT;
            plats[idx].posx[0] = x << 8;
            plats[idx].posx[1] = x << 8;
            plats[idx].posx[2] = x << 8;
            plats[idx].posy[0] = plat_layer_y[layer] << 8;
            plats[idx].posy[1] = plat_layer_y[layer] << 8;
            plats[idx].posy[2] = plat_layer_y[layer] << 8;
            plats[idx].velox = goes_right ? LEVEL_SPEED : -LEVEL_SPEED;
            plats[idx].veloy = 0;

            if (goes_right)
                x -= w + PLAT_GAP;
            else
                x += w + PLAT_GAP;
        }
    }

    while (1) {
        for (int i = 0; i < TOTAL_BONES; i++)
            draw_bone(&bones[i], 1, 0x0000, bounds_default);
        for (int i = 0; i < NUM_PLATFORMS; i++)
            erase_platform(&plats[i], 1, bounds_default);

        for (int i = 0; i < TOTAL_BONES; i++) {
            update_pos(bones[i].posx[0] + bones[i].velox, bones[i].posx);
            draw_bone(&bones[i], 0, 0xFFFF, bounds_default);
        }
        for (int i = 0; i < NUM_PLATFORMS; i++) {
            update_platform(&plats[i]);
            draw_platform(&plats[i], 0, bounds_default);
        }

        swap_buffers();

        // make sure that there is nothing on the screen before stopping
        int all_gone = 1;
        for (int i = 0; i < TOTAL_BONES && all_gone; i++) {
            int goes_right = (i / NUM_BONES_PER_ROW != 1);
            if (goes_right) {
                if (bones[i].posx[0] <= (right_border << 8)) all_gone = 0;
            } else {
                if (bones[i].posx[0] + (BONE_DRAW_WIDTH << 8) >= (left_border << 8)) all_gone = 0;
            }
        }
        for (int i = 0; i < NUM_PLATFORMS && all_gone; i++) {
            int goes_right = (i < PLATS_PER_LAYER);
            if (goes_right) {
                if (plats[i].posx[0] <= (right_border << 8)) all_gone = 0;
            } else {
                if (plats[i].posx[0] + (plats[i].width << 8) >= (left_border << 8)) all_gone = 0;
            }
        }
        if (all_gone) break;
    }
}