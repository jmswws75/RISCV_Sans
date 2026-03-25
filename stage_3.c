#include <math.h>

void run_stage_3() {
    struct Bone Bone_army[12];

    int bounds_default[4] = {70, 129, 251, 192};
    int bounds_unlimited[4] = {0, 0, 360, 240};

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
        int base_x = right_border + 213 * g;

        // white bottom
        Bone_army[i].color = 0xffff;
        Bone_army[i].length = 4;
        Bone_army[i].posx[0] = base_x << 8;
        Bone_army[i].posx[1] = base_x << 8;
        Bone_army[i].posx[2] = base_x << 8;
        Bone_army[i].posy[0] = 183 << 8;
        Bone_army[i].posy[1] = 183 << 8;
        Bone_army[i].posy[2] = 183 << 8;
        Bone_army[i].velox = -256;
        Bone_army[i].veloy = 0;

        // "blue" top
        Bone_army[i + 1].color = 0xffff;
        Bone_army[i + 1].length = 42;
        Bone_army[i + 1].posx[0] = (base_x + 65) << 8;
        Bone_army[i + 1].posx[1] = (base_x + 65) << 8;
        Bone_army[i + 1].posx[2] = (base_x + 65) << 8;
        Bone_army[i + 1].posy[0] = 129 << 8;
        Bone_army[i + 1].posy[1] = 129 << 8;
        Bone_army[i + 1].posy[2] = 129 << 8;
        Bone_army[i + 1].velox = -256;
        Bone_army[i + 1].veloy = 0;
    }

    while (1) {
        for (int i = 0; i < 6; i++) {
            draw_bone(&Bone_army[i], 1, 0x0000, bounds_default);
        }

        for (int i = 0; i < 6; i++) {
            update_pos(Bone_army[i].posx[0] + Bone_army[i].velox, Bone_army[i].posx);
            draw_bone(&Bone_army[i], 0, 0xffff, bounds_default);
        }

        swap_buffers();

        if (Bone_army[5].posx[0] <= ((left_border - 20) << 8)) {
            break;
        }
    }

    // Phase 2 from the left
    for (int g = 0; g < 3; g++) {
        int i = 6 + 2 * g;

        // each next set starts farther left so they enter one after another
        int base_x = left_border - 213 * g;

        // white bottom
        Bone_army[i].color = 0xffff;
        Bone_army[i].length = 4;
        Bone_army[i].posx[0] = base_x << 8;
        Bone_army[i].posx[1] = base_x << 8;
        Bone_army[i].posx[2] = base_x << 8;
        Bone_army[i].posy[0] = 183 << 8;
        Bone_army[i].posy[1] = 183 << 8;
        Bone_army[i].posy[2] = 183 << 8;
        Bone_army[i].velox = 256;
        Bone_army[i].veloy = 0;

        // "blue" top
        Bone_army[i + 1].color = 0xffff;
        Bone_army[i + 1].length = 42;
        Bone_army[i + 1].posx[0] = (base_x - 65) << 8;
        Bone_army[i + 1].posx[1] = (base_x - 65) << 8;
        Bone_army[i + 1].posx[2] = (base_x - 65) << 8;
        Bone_army[i + 1].posy[0] = 129 << 8;
        Bone_army[i + 1].posy[1] = 129 << 8;
        Bone_army[i + 1].posy[2] = 129 << 8;
        Bone_army[i + 1].velox = 256;
        Bone_army[i + 1].veloy = 0;
    }

    while (1) {
        for (int i = 6; i < 12; i++) {
            draw_bone(&Bone_army[i], 1, 0x0000, bounds_default);
        }

        for (int i = 6; i < 12; i++) {
            update_pos(Bone_army[i].posx[0] + Bone_army[i].velox, Bone_army[i].posx);
            draw_bone(&Bone_army[i], 0, 0xffff, bounds_default);
        }

        swap_buffers();

        if (Bone_army[11].posx[0] >= ((right_border + 20) << 8)) {
            break;
        }
    }
}