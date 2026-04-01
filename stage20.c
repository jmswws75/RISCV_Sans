#include "graphics.h"
#include "movement.h"
#include <stdlib.h>

#define BONE_WIDTH 5
#define BONE_SPACING 35
#define BOTTOM_BONE_HEIGHT 6
#define TOP_BONE_HEIGHT 42
#define LEVEL_SPEED 512

// we have a look up table for sin to avoid calculating floats
static const int sinValues[360] = {
       0,   4,   9,  13,  18,  22,  27,  31,  36,  40,
      44,  49,  53,  58,  62,  66,  71,  75,  79,  83,
      88,  92,  96, 100, 104, 108, 112, 116, 120, 124,
     128, 132, 136, 139, 143, 147, 150, 154, 158, 161,
     165, 168, 171, 175, 178, 181, 184, 187, 190, 193,
     196, 199, 202, 204, 207, 210, 212, 215, 217, 219,
     222, 224, 226, 228, 230, 232, 234, 236, 237, 239,
     241, 242, 243, 245, 246, 247, 248, 249, 250, 251,
     252, 253, 254, 254, 255, 255, 255, 256, 256, 256,
     256, 256, 256, 256, 255, 255, 255, 254, 254, 253,
     252, 251, 250, 249, 248, 247, 246, 245, 243, 242,
     241, 239, 237, 236, 234, 232, 230, 228, 226, 224,
     222, 219, 217, 215, 212, 210, 207, 204, 202, 199,
     196, 193, 190, 187, 184, 181, 178, 175, 171, 168,
     165, 161, 158, 154, 150, 147, 143, 139, 136, 132,
     128, 124, 120, 116, 112, 108, 104, 100,  96,  92,
      88,  83,  79,  75,  71,  66,  62,  58,  53,  49,
      44,  40,  36,  31,  27,  22,  18,  13,   9,   4,
       0,  -4,  -9, -13, -18, -22, -27, -31, -36, -40,
     -44, -49, -53, -58, -62, -66, -71, -75, -79, -83,
     -88, -92, -96,-100,-104,-108,-112,-116,-120,-124,
    -128,-132,-136,-139,-143,-147,-150,-154,-158,-161,
    -165,-168,-171,-175,-178,-181,-184,-187,-190,-193,
    -196,-199,-202,-204,-207,-210,-212,-215,-217,-219,
    -222,-224,-226,-228,-230,-232,-234,-236,-237,-239,
    -241,-242,-243,-245,-246,-247,-248,-249,-250,-251,
    -252,-253,-254,-254,-255,-255,-255,-256,-256,-256,
    -256,-256,-256,-256,-255,-255,-255,-254,-254,-253,
    -252,-251,-250,-249,-248,-247,-246,-245,-243,-242,
    -241,-239,-237,-236,-234,-232,-230,-228,-226,-224,
    -222,-219,-217,-215,-212,-210,-207,-204,-202,-199,
    -196,-193,-190,-187,-184,-181,-178,-175,-171,-168,
    -165,-161,-158,-154,-150,-147,-143,-139,-136,-132,
    -128,-124,-120,-116,-112,-108,-104,-100, -96, -92,
     -88, -83, -79, -75, -71, -66, -62, -58, -53, -49,
     -44, -40, -36, -31, -27, -22, -18, -13,  -9,  -4
};

static const int cosValues[360] = {
     256, 256, 256, 256, 255, 255, 255, 254, 254, 253,
     252, 251, 250, 249, 248, 247, 246, 245, 243, 242,
     241, 239, 237, 236, 234, 232, 230, 228, 226, 224,
     222, 219, 217, 215, 212, 210, 207, 204, 202, 199,
     196, 193, 190, 187, 184, 181, 178, 175, 171, 168,
     165, 161, 158, 154, 150, 147, 143, 139, 136, 132,
     128, 124, 120, 116, 112, 108, 104, 100,  96,  92,
      88,  83,  79,  75,  71,  66,  62,  58,  53,  49,
      44,  40,  36,  31,  27,  22,  18,  13,   9,   4,
       0,  -4,  -9, -13, -18, -22, -27, -31, -36, -40,
     -44, -49, -53, -58, -62, -66, -71, -75, -79, -83,
     -88, -92, -96,-100,-104,-108,-112,-116,-120,-124,
    -128,-132,-136,-139,-143,-147,-150,-154,-158,-161,
    -165,-168,-171,-175,-178,-181,-184,-187,-190,-193,
    -196,-199,-202,-204,-207,-210,-212,-215,-217,-219,
    -222,-224,-226,-228,-230,-232,-234,-236,-237,-239,
    -241,-242,-243,-245,-246,-247,-248,-249,-250,-251,
    -252,-253,-254,-254,-255,-255,-255,-256,-256,-256,
    -256,-256,-256,-256,-255,-255,-255,-254,-254,-253,
    -252,-251,-250,-249,-248,-247,-246,-245,-243,-242,
    -241,-239,-237,-236,-234,-232,-230,-228,-226,-224,
    -222,-219,-217,-215,-212,-210,-207,-204,-202,-199,
    -196,-193,-190,-187,-184,-181,-178,-175,-171,-168,
    -165,-161,-158,-154,-150,-147,-143,-139,-136,-132,
    -128,-124,-120,-116,-112,-108,-104,-100, -96, -92,
     -88, -83, -79, -75, -71, -66, -62, -58, -53, -49,
     -44, -40, -36, -31, -27, -22, -18, -13,  -9,  -4,
       0,   4,   9,  13,  18,  22,  27,  31,  36,  40,
      44,  49,  53,  58,  62,  66,  71,  75,  79,  83,
      88,  92,  96, 100, 104, 108, 112, 116, 120, 124,
     128, 132, 136, 139, 143, 147, 150, 154, 158, 161,
     165, 168, 171, 175, 178, 181, 184, 187, 190, 193,
     196, 199, 202, 204, 207, 210, 212, 215, 217, 219,
     222, 224, 226, 228, 230, 232, 234, 236, 237, 239,
     241, 242, 243, 245, 246, 247, 248, 249, 250, 251,
     252, 253, 254, 254, 255, 255, 255, 256, 256, 256
};

int run_stage_20(int *Global_health) {

    int bounds_default[4] = {123, 116, 199, 192};
    int bounds_long_p[4] = {0, 116, 20, 192};
    int bounds_long[4] = {0, 116, 319, 192};
    int bounds_unlimited[4] = {0, 0, 319, 239};
	
	graphics_init();
    
	struct player player1;
    struct Sans sans;
    sans.centerx = 161;
    sans.centery = 83;

    struct Head head;
    head.centerx = 161;
    head.centery = 83;

    struct Zz z;
    z.centerx = 161 + 31;
    z.centery = 83 - 24;
    player1.ground = (192 - 5) << 8;
    for (int i = 0; i < 3; i++) {
        player1.posx[i] = 157 << 8;
        player1.posy[i] = 150 << 8;
    }
    player1.was_up_pressed = false;
    player1.have_gravity = false;
    
    for (int i = 0; i< 4; i++) {
        player1.bounds[i] = bounds_default[i];
    }
    player1.health = *Global_health;
    player1.gravity = 8;
    player1.veloY = 0;
    player1.burst_force = 400;
	
	clear_screen();
    draw_rectangle(120, 113, 202, 115, 0xFFFF, bounds_unlimited);
    draw_rectangle(120, 113, 122, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(120, 193, 202, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);
    swap_buffers();

    draw_rectangle(120, 113, 202, 115, 0xFFFF, bounds_unlimited);
    draw_rectangle(120, 113, 122, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(120, 193, 202, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);
    swap_buffers();
	
    { // bottom bone
        // snap player to bottom
        int frameCount = 0;
        while (1) {
            sans.centerx = 161;
            sans.centery = 83;
            draw_sans(&sans, bounds_unlimited);
            draw_head(&head, bounds_unlimited);
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap player to bottom
            if (player1.posy[0] < player1.ground) {
                player1.posy[0] += 4 << 8;
                if (player1.posy[0] > player1.ground) {player1.posy[0] = player1.ground;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0; // reset frameCount

        // substage0-1: red lines
        while (1) {
            
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            draw_rectangle_outline(124, 166, 198, 191, 0xf800);
            swap_buffers();
            frameCount++;
        }

        frameCount = 0;
        draw_rectangle_outline(124, 166, 198, 191, 0x0000);
        swap_buffers();
        draw_rectangle_outline(124, 166, 198, 191, 0x0000);

        // substage1: bottom bone
        struct Bone bone_army_1[20];
        for (int i = 0; i < 20; i++) {
            bone_army_1[i].posx[0] = (199 - 7 * i) << 8;
            bone_army_1[i].posx[1] = (199 - 7 * i )<< 8;
            bone_army_1[i].posx[2] = (199 - 7 * i )<< 8;
            bone_army_1[i].posy[0] = 196 << 8;
            bone_army_1[i].posy[1] = 196 << 8;
            bone_army_1[i].posy[2] = 196 << 8;
            bone_army_1[i].length = 30;
            bone_army_1[i].velox = 0;
            bone_army_1[i].veloy = -2048;
            bone_army_1[i].color = 0xFFFF;
        }

        while (1) {
            
            if (frameCount > 60) {
                break;
            }

            for (int i = 0; i < 20; i++) {
                draw_bone(&bone_army_1[i], 1, 0x0000, bounds_default); //erase old one
            }

            draw_player(&player1, 1, 0x0000);

            for (int i = 0; i < 20; i++) {
                if(bone_army_1[i].posy[0] <= 166 << 8) {
                    bone_army_1[i].veloy = 0;
                }
                if (frameCount > 55) {
                    bone_army_1[i].veloy = 2048;
                }

                update_pos(bone_army_1[i].posy[0] + bone_army_1[i].veloy, bone_army_1[i].posy); 

                draw_bone(&bone_army_1[i], 0, 0xffff, bounds_default); //draw new one
            }
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;

        }
    }

    { // right bone
        int frameCount = 0;
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap
            if (player1.posx[0] < (player1.bounds[2] - 5) << 8) {
                player1.posx[0] += 4 << 8;
                if (player1.posx[0] > (player1.bounds[2] - 5) << 8) {player1.posx[0] = (player1.bounds[2] - 5) << 8;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0; // reset frameCount

        // substage0-1: red lines
        while (1) {

            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            draw_rectangle_outline(173, 117, 198, 191, 0xf800);
            swap_buffers();
            frameCount++;
        }

        frameCount = 0;
        draw_rectangle_outline(173, 117, 198, 191, 0x0000);
        swap_buffers();
        draw_rectangle_outline(173, 117, 198, 191, 0x0000);

        // right bone
        struct Bone bone_army_1[20];
        for (int i = 0; i < 20; i++) {
            bone_army_1[i].posx[0] = 203 << 8;
            bone_army_1[i].posx[1] = 203 << 8;
            bone_army_1[i].posx[2] = 203 << 8;
            bone_army_1[i].posy[0] = (116 + 7*i) << 8;
            bone_army_1[i].posy[1] = (116 + 7*i) << 8;
            bone_army_1[i].posy[2] = (116 + 7*i) << 8;
            bone_army_1[i].length = 30;
            bone_army_1[i].velox = -2048;
            bone_army_1[i].veloy = 0;
            bone_army_1[i].color = 0xFFFF;
        }

        while (1) {
            
            if (frameCount > 60) {
                break;
            }

            for (int i = 0; i < 20; i++) {
                draw_bone_h(&bone_army_1[i], 1, 0x0000, bounds_default); //erase old one
            }

            draw_player(&player1, 1, 0x0000);

            for (int i = 0; i < 20; i++) {
                if(bone_army_1[i].posx[0] <= 173 << 8) {
                    bone_army_1[i].velox = 0;
                }
                if (frameCount > 55) {
                    bone_army_1[i].velox = 2048;
                }

                update_pos(bone_army_1[i].posx[0] + bone_army_1[i].velox, bone_army_1[i].posx); 

                draw_bone_h(&bone_army_1[i], 0, 0xffff, bounds_default); //draw new one
            }
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;

        }
    }

    { // top bone
        int frameCount = 0;
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap player to bottom
            if (player1.posy[0] > (player1.bounds[1] << 8)) {
                player1.posy[0] -= 4 << 8;
                if (player1.posy[0] < (player1.bounds[1] << 8)) {player1.posy[0] = (player1.bounds[1] << 8);}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0; // reset frameCount

        // substage0-1: red lines
        while (1) {

            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            draw_rectangle_outline(124, 117, 198, 142, 0xf800);
            swap_buffers();
            frameCount++;
        }

        frameCount = 0;
        // default bound is {123, 116, 199, 192}
        draw_rectangle_outline(124, 117, 198, 142, 0x0000);
        swap_buffers();
        draw_rectangle_outline(124, 117, 198, 142, 0x0000);

        // substage1: bottom bone
        struct Bone bone_army_1[20];
        for (int i = 0; i < 20; i++) {
            bone_army_1[i].posx[0] = (199 - 7 * i) << 8;
            bone_army_1[i].posx[1] = (199 - 7 * i )<< 8;
            bone_army_1[i].posx[2] = (199 - 7 * i )<< 8;
            bone_army_1[i].posy[0] = 75 << 8;
            bone_army_1[i].posy[1] = 75 << 8;
            bone_army_1[i].posy[2] = 75 << 8;
            bone_army_1[i].length = 30;
            bone_army_1[i].velox = 0;
            bone_army_1[i].veloy = 2048;
            bone_army_1[i].color = 0xFFFF;
        }

        while (1) {
            
            if (frameCount > 60) {
                break;
            }

            for (int i = 0; i < 20; i++) {
                draw_bone(&bone_army_1[i], 1, 0x0000, bounds_default); //erase old one
            }

            draw_player(&player1, 1, 0x0000);

            for (int i = 0; i < 20; i++) {
                if(bone_army_1[i].posy[0] >= 106 << 8) {
                    bone_army_1[i].veloy = 0;
                }
                if (frameCount > 55) {
                    bone_army_1[i].veloy = -2048;
                }

                update_pos(bone_army_1[i].posy[0] + bone_army_1[i].veloy, bone_army_1[i].posy); 

                draw_bone(&bone_army_1[i], 0, 0xffff, bounds_default); //draw new one
            }
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;

        }
    }

    { // left bone
        int frameCount = 0;
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap left
            if (player1.posx[0] > (player1.bounds[0]) << 8) {
                player1.posx[0] -= 4 << 8;
                if (player1.posx[0] < (player1.bounds[0]) << 8) {player1.posx[0] = (player1.bounds[0]) << 8;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0; // reset frameCount

        // substage0-1: red lines
        while (1) {

            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            // default bound is {123, 116, 199, 192}
            draw_rectangle_outline(124, 117, 150, 191, 0xf800);
            swap_buffers();
            frameCount++;
        }

        frameCount = 0;
        draw_rectangle_outline(124, 117, 150, 191, 0x0000);
        swap_buffers();
        draw_rectangle_outline(124, 117, 150, 191, 0x0000);

        // left bone
        struct Bone bone_army_1[20];
        for (int i = 0; i < 20; i++) {
            bone_army_1[i].posx[0] = 83 << 8;
            bone_army_1[i].posx[1] = 83 << 8;
            bone_army_1[i].posx[2] = 83 << 8;
            bone_army_1[i].posy[0] = (116 + 7*i) << 8;
            bone_army_1[i].posy[1] = (116 + 7*i) << 8;
            bone_army_1[i].posy[2] = (116 + 7*i) << 8;
            bone_army_1[i].length = 30;
            bone_army_1[i].velox = 2048;
            bone_army_1[i].veloy = 0;
            bone_army_1[i].color = 0xFFFF;
        }

        while (1) {
            
            if (frameCount > 60) {
                break;
            }

            for (int i = 0; i < 20; i++) {
                draw_bone_h(&bone_army_1[i], 1, 0x0000, bounds_default); //erase old one
            }

            draw_player(&player1, 1, 0x0000);

            for (int i = 0; i < 20; i++) {
                if(bone_army_1[i].posx[0] >= 113 << 8) {
                    bone_army_1[i].velox = 0;
                }
                if (frameCount > 55) {
                    bone_army_1[i].velox = -2048;
                }

                update_pos(bone_army_1[i].posx[0] + bone_army_1[i].velox, bone_army_1[i].posx); 

                draw_bone_h(&bone_army_1[i], 0, 0xffff, bounds_default); //draw new one
            }
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;

        }
    }

    // VERTICAL BONE SLIDE
    struct Bone left_bones[4];
    struct Bone right_bones[4];

    for (int i = 0; i < 4; i++) {
		left_bones[i].color = 0xFFFF;
        left_bones[i].length = 92;
        left_bones[i].posx[0] = 65 << 8;
        left_bones[i].posx[1] = 65 << 8;
        left_bones[i].posx[2] = 65 << 8;
        left_bones[i].posy[0] = (-80 * i) << 8;
        left_bones[i].posy[1] = (-80 * i) << 8;
        left_bones[i].posy[2] = (-80 * i) << 8;
        left_bones[i].velox = 0;
        left_bones[i].veloy = LEVEL_SPEED;
	}
	
	for (int i = 0; i < 4; i++) {
		right_bones[i].color = 0xFFFF;
        right_bones[i].length = 92;
        right_bones[i].posx[0] = 165 << 8;
        right_bones[i].posx[1] = 165 << 8;
        right_bones[i].posx[2] = 165 << 8;
        right_bones[i].posy[0] = 240 + (80 * i) << 8;
        right_bones[i].posy[1] = 240+ (80 * i) << 8;
        right_bones[i].posy[2] = 240+ (80 * i) << 8;
        right_bones[i].velox = 0;
        right_bones[i].veloy = -LEVEL_SPEED;
	}
	
    int frame_count = 0;
	
    while (1) {
        sans.centerx = 161;
        sans.centery = 83;
        for (int i = 0; i < 4; i++) {
			draw_bone_h(&left_bones[i], 1, 0x0000, bounds_unlimited);
            draw_sans(&sans, bounds_unlimited);
            draw_head(&head, bounds_unlimited);
		}
		
		for (int i = 0; i < 4; i++) {
			draw_bone_h(&right_bones[i], 1, 0x0000, bounds_unlimited);
            draw_sans(&sans, bounds_unlimited);
            draw_head(&head, bounds_unlimited);
		}
		
		draw_player(&player1, 1, 0x0000);
		
		draw_rectangle(120, 113, 202, 115, 0xFFFF, bounds_unlimited);
		draw_rectangle(120, 113, 122, 195, 0xFFFF, bounds_unlimited);
		draw_rectangle(120, 193, 202, 195, 0xFFFF, bounds_unlimited);
		draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);
		
		for (int i = 0; i < 4; i++) {
            update_pos(left_bones[i].posy[0] + left_bones[i].veloy, left_bones[i].posy);
            draw_bone_h(&left_bones[i], 0, 0xFFFF, bounds_unlimited);
        }
		
		for (int i = 0; i < 4; i++) {
            update_pos(right_bones[i].posy[0] + right_bones[i].veloy, right_bones[i].posy);
            draw_bone_h(&right_bones[i], 0, 0xFFFF, bounds_unlimited);
        }
		
		movement(&player1, NULL, 0);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);
        if (player1.health == 0) {return 1;}
		
        swap_buffers();

        // stop condition
        
		frame_count++;
		
		if (frame_count >= 260) {break;}
		
    }

    int frameCount = 0;

    // snap to the left border
    while (1) {
        if (frameCount > 20) {
            break;
        }

        draw_player(&player1, 1, 0x0000);
        movement(&player1, NULL, 0);
        // snap
        if (player1.posx[0] > (player1.bounds[0]) << 8) {
            player1.posx[0] -= 4 << 8;
            if (player1.posx[0] < (player1.bounds[0]) << 8) {player1.posx[0] = (player1.bounds[0]) << 8;}
        }
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);

        if (player1.health == 0) {return 1;}

        swap_buffers();
        frameCount++;
    }

    for (int i = 0; i < 40; i++) {

        draw_player(&player1, 0, 0xf800);
        draw_rectangle(200, 113, 320, 195, 0x0000, bounds_unlimited); // clear
        draw_rectangle(0, 113, 123, 195, 0x0000, bounds_unlimited); // clear
        
        draw_rectangle(120 - 4*i, 113, 202 + 4*i, 115, 0xFFFF, bounds_unlimited); // top line
		draw_rectangle(120 - 4*i, 113, 122 - 4*i, 195, 0xFFFF, bounds_unlimited); // left line
		draw_rectangle(120 - 4*i, 193, 202 + 4*i, 195, 0xFFFF, bounds_unlimited); // bottom line
		draw_rectangle(200 + 4*i, 113, 202 + 4*i, 195, 0xFFFF, bounds_unlimited); // right line
        swap_buffers();
        
    }

    for (int i = 0; i< 4; i++) {
        player1.bounds[i] = bounds_unlimited[i];
    }

    for (int i = 0; i < 40; i++) {

        draw_player(&player1, 1, 0x0000);
        movement(&player1, NULL, 0);
        if (player1.posx[0] > 15 << 8) {
            player1.posx[0] -= 3 << 8;
            if (player1.posx[0] < 15 << 8) {player1.posx[0] = 15 << 8;}
        }

        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);

        swap_buffers();

    }

    for (int i = 0; i< 4; i++) {
        player1.bounds[i] = bounds_long_p[i];
    }

    { // sin wave
        struct Bone bone_army_1[130];

        for (int i = 0; i < 65; i++) {

            int sinValue = sin( (i - 4.5) / 2.8 ) * 16;
            
            bone_army_1[i].posx[0] = (320 + 25 * i) << 8;
            bone_army_1[i].posx[1] = (320 + 25 * i) << 8;
            bone_army_1[i].posx[2] = (320 + 25 * i) << 8;
            bone_army_1[i].posy[0] = 117 << 8;
            bone_army_1[i].posy[1] = 117 << 8;
            bone_army_1[i].posy[2] = 117 << 8;
            bone_army_1[i].length = 20 + sinValue;
            bone_army_1[i].velox = -1500;
            bone_army_1[i].veloy = 0;
            bone_army_1[i].color = 0xFFFF;

            int posy = 117 + (int)(41 + sinValue) << 8;

            bone_army_1[i+65].posx[0] = (320 + 25 * i) << 8;
            bone_army_1[i+65].posx[1] = (320 + 25 * i) << 8;
            bone_army_1[i+65].posx[2] = (320 + 25 * i) << 8;
            bone_army_1[i+65].posy[0] = posy;
            bone_army_1[i+65].posy[1] = posy;
            bone_army_1[i+65].posy[2] = posy;
            bone_army_1[i+65].length = 186 - (posy >> 8);
            bone_army_1[i+65].velox = -1500;
            bone_army_1[i+65].veloy = 0;
            bone_army_1[i+65].color = 0xFFFF;
        }

        int frame_count = 0;

        while (1) {
            
            for (int i = 0; i < 130; i++) {
                draw_bone(&bone_army_1[i], 1, 0x0000, bounds_long); //erase old one
            }

            draw_player(&player1, 1, 0x0000);

            for (int i = 0; i < 130; i++) {
                update_pos(bone_army_1[i].posx[0] + bone_army_1[i].velox, bone_army_1[i].posx); 
                draw_bone(&bone_army_1[i], 0, 0xffff, bounds_long); //draw new one
            }
            
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            
            frame_count++;

            if (frame_count >= 350){
                break;
            }

        }
    }

    { // top bottom groups of 3
        // bounds_long[4] = {0, 116, 319, 192};
        struct Bone bone_army_1[27];

        // top
        for (int i = 0; i < 15; i+=3) {
            bone_army_1[i].posx[0] = (320 + 117 * i) << 8;
            bone_army_1[i].posx[1] = (320 + 117 * i) << 8;
            bone_army_1[i].posx[2] = (320 + 117 * i) << 8;
            bone_army_1[i].posy[0] = 117 << 8;
            bone_army_1[i].posy[1] = 117 << 8;
            bone_army_1[i].posy[2] = 117 << 8;
            bone_army_1[i].length = 32;
            bone_army_1[i].velox = -2048;
            bone_army_1[i].veloy = 0;
            bone_army_1[i].color = 0xFFFF;

            bone_army_1[i+1].posx[0] = (320 + 117 * i + 10) << 8;
            bone_army_1[i+1].posx[1] = (320 + 117 * i + 10) << 8;
            bone_army_1[i+1].posx[2] = (320 + 117 * i + 10) << 8;
            bone_army_1[i+1].posy[0] = 117 << 8;
            bone_army_1[i+1].posy[1] = 117 << 8;
            bone_army_1[i+1].posy[2] = 117 << 8;
            bone_army_1[i+1].length = 32;
            bone_army_1[i+1].velox = -2048;
            bone_army_1[i+1].veloy = 0;
            bone_army_1[i+1].color = 0xFFFF;

            bone_army_1[i+2].posx[0] = (320 + 117 * i + 20) << 8;
            bone_army_1[i+2].posx[1] = (320 + 117 * i + 20) << 8;
            bone_army_1[i+2].posx[2] = (320 + 117 * i + 20) << 8;
            bone_army_1[i+2].posy[0] = 117 << 8;
            bone_army_1[i+2].posy[1] = 117 << 8;
            bone_army_1[i+2].posy[2] = 117 << 8;
            bone_army_1[i+2].length = 32;
            bone_army_1[i+2].velox = -2048;
            bone_army_1[i+2].veloy = 0;
            bone_army_1[i+2].color = 0xFFFF;
        }

        for (int i = 0; i < 12; i+=3) {
            bone_army_1[i+15].posx[0] = (320 + 180 + 117 * i) << 8;
            bone_army_1[i+15].posx[1] = (320 + 180 + 117 * i) << 8;
            bone_army_1[i+15].posx[2] = (320 + 190 + 117 * i) << 8;
            bone_army_1[i+15].posy[0] = 153 << 8;
            bone_army_1[i+15].posy[1] = 153 << 8;
            bone_army_1[i+15].posy[2] = 153 << 8;
            bone_army_1[i+15].length = 32;
            bone_army_1[i+15].velox = -2048;
            bone_army_1[i+15].veloy = 0;
            bone_army_1[i+15].color = 0xFFFF;

            bone_army_1[i+16].posx[0] = (320 + 180 + 117 * i + 10) << 8;
            bone_army_1[i+16].posx[1] = (320 + 180 + 117 * i + 10) << 8;
            bone_army_1[i+16].posx[2] = (320 + 180 + 117 * i + 10) << 8;
            bone_army_1[i+16].posy[0] = 153 << 8;
            bone_army_1[i+16].posy[1] = 153 << 8;
            bone_army_1[i+16].posy[2] = 153 << 8;
            bone_army_1[i+16].length = 32;
            bone_army_1[i+16].velox = -2048;
            bone_army_1[i+16].veloy = 0;
            bone_army_1[i+16].color = 0xFFFF;

            bone_army_1[i+17].posx[0] = (320 + 180 + 117 * i + 20) << 8;
            bone_army_1[i+17].posx[1] = (320 + 180 + 117 * i + 20) << 8;
            bone_army_1[i+17].posx[2] = (320 + 180 + 117 * i + 20) << 8;
            bone_army_1[i+17].posy[0] = 153 << 8;
            bone_army_1[i+17].posy[1] = 153 << 8;
            bone_army_1[i+17].posy[2] = 153 << 8;
            bone_army_1[i+17].length = 32;
            bone_army_1[i+17].velox = -2048;
            bone_army_1[i+17].veloy = 0;
            bone_army_1[i+17].color = 0xFFFF;
        }

        int frame_count = 0;

        while (1) {
            
            for (int i = 0; i < 27; i++) {
                draw_bone(&bone_army_1[i], 1, 0x0000, bounds_long); //erase old one
            }

            draw_player(&player1, 1, 0x0000);

            for (int i = 0; i < 27; i++) {
                update_pos(bone_army_1[i].posx[0] + bone_army_1[i].velox, bone_army_1[i].posx); 
                draw_bone(&bone_army_1[i], 0, 0xffff, bounds_long); //draw new one
            }
            
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            
            frame_count++;

            if (frame_count >= 250){
                break;
            }

        }
    }

    // cone
    {
        struct Bone bone_army_1[54];

        // bounds_long[4] = {0, 116, 319, 192};
        for (int i = 0; i < 27; i++) {

            int sinValue = sin( (i - 4.5) / 2.8 ) * 16;
            
            bone_army_1[i].posx[0] = (320 + 50 * i) << 8;
            bone_army_1[i].posx[1] = (320 + 50 * i) << 8;
            bone_army_1[i].posx[2] = (320 + 50 * i) << 8;
            bone_army_1[i].posy[0] = 117 << 8;
            bone_army_1[i].posy[1] = 117 << 8;
            bone_army_1[i].posy[2] = 117 << 8;
            bone_army_1[i].length = i;
            bone_army_1[i].velox = -3000;
            bone_army_1[i].veloy = 0;
            bone_army_1[i].color = 0xFFFF;

            int posy = 117 + (int)(41 + sinValue) << 8;

            bone_army_1[i+27].posx[0] = (320 + 50 * i) << 8;
            bone_army_1[i+27].posx[1] = (320 + 50 * i) << 8;
            bone_army_1[i+27].posx[2] = (320 + 50 * i) << 8;
            bone_army_1[i+27].posy[0] = (192 - 1 - 6 - i) << 8;
            bone_army_1[i+27].posy[1] = (192 - 1 - 6 - i) << 8;
            bone_army_1[i+27].posy[2] = (192 - 1 - 6 - i) << 8;
            bone_army_1[i+27].length = i;
            bone_army_1[i+27].velox = -3000;
            bone_army_1[i+27].veloy = 0;
            bone_army_1[i+27].color = 0xFFFF;
        }

        int frame_count = 0;

        while (1) {
            
            for (int i = 0; i < 54; i++) {
                draw_bone(&bone_army_1[i], 1, 0x0000, bounds_long); //erase old one
            }

            draw_player(&player1, 1, 0x0000);

            for (int i = 0; i < 54; i++) {
                update_pos(bone_army_1[i].posx[0] + bone_army_1[i].velox, bone_army_1[i].posx); 
                draw_bone(&bone_army_1[i], 0, 0xffff, bounds_long); //draw new one
            }
            
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            
            frame_count++;

            if (frame_count >= 200){
                break;
            }

        }
    }

    // bounds_default[4] = {123, 116, 199, 192};
    for (int i = 0; i < 30; i++) {

        draw_player(&player1, 0, 0xf800);
        draw_rectangle(200, 113, 320, 195, 0x0000, bounds_unlimited); // clear
        
        draw_rectangle(0, 113, 319 - 4*i, 115, 0xFFFF, bounds_unlimited); // top line
		draw_rectangle(0, 193, 319 - 4*i, 195, 0xFFFF, bounds_unlimited); // bottom line
		draw_rectangle(319 - 4*i, 113, 322 - 4*i, 195, 0xFFFF, bounds_unlimited); // right line
        swap_buffers();
        
    }

    draw_rectangle(200, 113, 320, 195, 0x0000, bounds_unlimited); // clear

    draw_rectangle(0, 113, 200, 115, 0xFFFF, bounds_unlimited); // top line
	draw_rectangle(0, 193, 200, 195, 0xFFFF, bounds_unlimited); // bottom line
	draw_rectangle(199, 113, 203, 195, 0xFFFF, bounds_unlimited); // right line
    swap_buffers();

    draw_rectangle(200, 113, 320, 195, 0x0000, bounds_unlimited); // clear

    draw_rectangle(0, 113, 200, 115, 0xFFFF, bounds_unlimited); // top line
	draw_rectangle(0, 193, 200, 195, 0xFFFF, bounds_unlimited); // bottom line
	draw_rectangle(199, 113, 203, 195, 0xFFFF, bounds_unlimited); // right line
    swap_buffers();

    // snap to the right border
    player1.bounds[2] = 199 - 5;

    frameCount = 0;

    while (1) {
        if (frameCount > 60) {
            break;
        }

        draw_player(&player1, 1, 0x0000);
        movement(&player1, NULL, 0);
        // snap
        if (player1.posx[0] < (player1.bounds[2]) << 8) {
            player1.posx[0] += 4 << 8;
            if (player1.posx[0] > (player1.bounds[2]) << 8) {player1.posx[0] = (player1.bounds[2]) << 8;}
        }
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);

        if (player1.health == 0) {return 1;}

        swap_buffers();
        frameCount++;
    }

    { // right bone
        int frameCount = 0;
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap
            if (player1.posx[0] < (player1.bounds[2]) << 8) {
                player1.posx[0] += 4 << 8;
                if (player1.posx[0] > (player1.bounds[2]) << 8) {player1.posx[0] = (player1.bounds[2]) << 8;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0; // reset frameCount

        // substage0-1: red lines
        while (1) {

            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            draw_rectangle_outline(173, 117, 198, 191, 0xf800);
            swap_buffers();
            frameCount++;
        }

        frameCount = 0;
        draw_rectangle_outline(173, 117, 198, 191, 0x0000);
        swap_buffers();
        draw_rectangle_outline(173, 117, 198, 191, 0x0000);

        // right bone
        struct Bone bone_army_1[20];
        for (int i = 0; i < 20; i++) {
            bone_army_1[i].posx[0] = 203 << 8;
            bone_army_1[i].posx[1] = 203 << 8;
            bone_army_1[i].posx[2] = 203 << 8;
            bone_army_1[i].posy[0] = (116 + 7*i) << 8;
            bone_army_1[i].posy[1] = (116 + 7*i) << 8;
            bone_army_1[i].posy[2] = (116 + 7*i) << 8;
            bone_army_1[i].length = 30;
            bone_army_1[i].velox = -2048;
            bone_army_1[i].veloy = 0;
            bone_army_1[i].color = 0xFFFF;
        }

        while (1) {
            
            if (frameCount > 60) {
                break;
            }

            for (int i = 0; i < 20; i++) {
                draw_bone_h(&bone_army_1[i], 1, 0x0000, bounds_default); //erase old one
            }

            draw_player(&player1, 1, 0x0000);

            for (int i = 0; i < 20; i++) {
                if(bone_army_1[i].posx[0] <= 173 << 8) {
                    bone_army_1[i].velox = 0;
                }
                if (frameCount > 55) {
                    bone_army_1[i].velox = 2048;
                }

                update_pos(bone_army_1[i].posx[0] + bone_army_1[i].velox, bone_army_1[i].posx); 

                draw_bone_h(&bone_army_1[i], 0, 0xffff, bounds_default); //draw new one
            }
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;

        }
    }

    for (int i = 0; i< 4; i++) {
        player1.bounds[i] = bounds_default[i];
    }

    clear_screen();
    draw_rectangle(120, 113, 202, 115, 0xFFFF, bounds_unlimited);
    draw_rectangle(120, 113, 122, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(120, 193, 202, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);
    swap_buffers();

    clear_screen();
    draw_rectangle(120, 113, 202, 115, 0xFFFF, bounds_unlimited);
    draw_rectangle(120, 113, 122, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(120, 193, 202, 195, 0xFFFF, bounds_unlimited);
    draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);
    swap_buffers();

    { // top and bottom bone
        int frameCount = 0;
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap player to bottom
            if (player1.posy[0] < player1.ground) {
                player1.posy[0] += 4 << 8;
                if (player1.posy[0] > player1.ground) {player1.posy[0] = player1.ground;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0; // reset frameCount

        // substage0-1: red lines
        while (1) {
            sans.centerx = 161;
            sans.centery = 83;
            draw_sans(&sans, bounds_unlimited);
            draw_head(&head, bounds_unlimited);
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            draw_rectangle_outline(124, 166, 198, 191, 0xf800);
            draw_rectangle_outline(124, 117, 198, 142, 0xf800);
            swap_buffers();
            frameCount++;
        }

        frameCount = 0;
        // default bound is {123, 116, 199, 192}
        draw_rectangle_outline(124, 117, 198, 142, 0x0000);
        draw_rectangle_outline(124, 166, 198, 191, 0x0000);
        swap_buffers();
        draw_rectangle_outline(124, 117, 198, 142, 0x0000);
        draw_rectangle_outline(124, 166, 198, 191, 0x0000);

        // substage1: bottom bone
        struct Bone bone_army_1[20];
        struct Bone bone_army_2[20];
        for (int i = 0; i < 20; i++) {
            bone_army_1[i].posx[0] = (199 - 7 * i) << 8;
            bone_army_1[i].posx[1] = (199 - 7 * i )<< 8;
            bone_army_1[i].posx[2] = (199 - 7 * i )<< 8;
            bone_army_1[i].posy[0] = 75 << 8;
            bone_army_1[i].posy[1] = 75 << 8;
            bone_army_1[i].posy[2] = 75 << 8;
            bone_army_1[i].length = 30;
            bone_army_1[i].velox = 0;
            bone_army_1[i].veloy = 2048;
            bone_army_1[i].color = 0xFFFF;
        }

        for (int i = 0; i < 20; i++) {
            bone_army_2[i].posx[0] = (199 - 7 * i) << 8;
            bone_army_2[i].posx[1] = (199 - 7 * i )<< 8;
            bone_army_2[i].posx[2] = (199 - 7 * i )<< 8;
            bone_army_2[i].posy[0] = 196 << 8;
            bone_army_2[i].posy[1] = 196 << 8;
            bone_army_2[i].posy[2] = 196 << 8;
            bone_army_2[i].length = 30;
            bone_army_2[i].velox = 0;
            bone_army_2[i].veloy = -2048;
            bone_army_2[i].color = 0xFFFF;
        }

        while (1) {
            sans.centerx = 161;
            sans.centery = 83;
            draw_sans(&sans, bounds_unlimited);
            draw_head(&head, bounds_unlimited);
            if (frameCount > 60) {
                break;
            }

            for (int i = 0; i < 20; i++) {
                draw_bone(&bone_army_1[i], 1, 0x0000, bounds_default); //erase old one
                draw_bone(&bone_army_2[i], 1, 0x0000, bounds_default); //erase old one
            }

            draw_player(&player1, 1, 0x0000);

            for (int i = 0; i < 20; i++) {
                if(bone_army_1[i].posy[0] >= 106 << 8) {
                    bone_army_1[i].veloy = 0;
                }
                if (frameCount > 55) {
                    bone_army_1[i].veloy = -2048;
                }

                if(bone_army_2[i].posy[0] <= 166 << 8) {
                    bone_army_2[i].veloy = 0;
                }
                if (frameCount > 55) {
                    bone_army_2[i].veloy = 2048;
                }


                update_pos(bone_army_1[i].posy[0] + bone_army_1[i].veloy, bone_army_1[i].posy); 
                update_pos(bone_army_2[i].posy[0] + bone_army_2[i].veloy, bone_army_2[i].posy); 

                draw_bone(&bone_army_1[i], 0, 0xffff, bounds_default); //draw new one
                draw_bone(&bone_army_2[i], 0, 0xffff, bounds_default); //draw new one
            }
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;

        }
    }

    { // top and left bone
        int frameCount = 0;
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap player to top
            if (player1.posy[0] > (player1.bounds[1] << 8)) {
                player1.posy[0] -= 4 << 8;
                if (player1.posy[0] < (player1.bounds[1] << 8)) {player1.posy[0] = (player1.bounds[1] << 8);}
            }
            // snap left
            if (player1.posx[0] > (player1.bounds[0]) << 8) {
                player1.posx[0] -= 4 << 8;
                if (player1.posx[0] < (player1.bounds[0]) << 8) {player1.posx[0] = (player1.bounds[0]) << 8;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0; // reset frameCount

        // substage0-1: red lines
        while (1) {

            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}


            draw_rectangle_outline(124, 117, 198, 142, 0xf800);
            draw_rectangle_outline(124, 117, 150, 191, 0xf800);
            swap_buffers();
            frameCount++;
        }

        frameCount = 0;
        // default bound is {123, 116, 199, 192}
        draw_rectangle_outline(124, 117, 198, 142, 0x0000);
        draw_rectangle_outline(124, 117, 150, 191, 0x0000);
        swap_buffers();
        draw_rectangle_outline(124, 117, 198, 142, 0x0000);
        draw_rectangle_outline(124, 117, 150, 191, 0x0000);

        // substage1: bottom bone
        struct Bone bone_army_1[20];
        struct Bone bone_army_2[20];
        for (int i = 0; i < 20; i++) {
            bone_army_1[i].posx[0] = (199 - 7 * i) << 8;
            bone_army_1[i].posx[1] = (199 - 7 * i )<< 8;
            bone_army_1[i].posx[2] = (199 - 7 * i )<< 8;
            bone_army_1[i].posy[0] = 75 << 8;
            bone_army_1[i].posy[1] = 75 << 8;
            bone_army_1[i].posy[2] = 75 << 8;
            bone_army_1[i].length = 30;
            bone_army_1[i].velox = 0;
            bone_army_1[i].veloy = 2048;
            bone_army_1[i].color = 0xFFFF;
        }

        for (int i = 0; i < 20; i++) {
            bone_army_2[i].posx[0] = 83 << 8;
            bone_army_2[i].posx[1] = 83 << 8;
            bone_army_2[i].posx[2] = 83 << 8;
            bone_army_2[i].posy[0] = (116 + 7*i) << 8;
            bone_army_2[i].posy[1] = (116 + 7*i) << 8;
            bone_army_2[i].posy[2] = (116 + 7*i) << 8;
            bone_army_2[i].length = 30;
            bone_army_2[i].velox = 2048;
            bone_army_2[i].veloy = 0;
            bone_army_2[i].color = 0xFFFF;
        }

        while (1) {
            
            if (frameCount > 60) {
                break;
            }

            for (int i = 0; i < 20; i++) {
                draw_bone(&bone_army_1[i], 1, 0x0000, bounds_default); //erase old one
                draw_bone_h(&bone_army_2[i], 1, 0x0000, bounds_default); //erase old one
            }

            draw_player(&player1, 1, 0x0000);

            for (int i = 0; i < 20; i++) {
                if(bone_army_1[i].posy[0] >= 106 << 8) {
                    bone_army_1[i].veloy = 0;
                }
                if (frameCount > 55) {
                    bone_army_1[i].veloy = -2048;
                }

                if(bone_army_2[i].posx[0] >= 113 << 8) {
                    bone_army_2[i].velox = 0;
                }
                if (frameCount > 55) {
                    bone_army_2[i].velox = -2048;
                }

                update_pos(bone_army_1[i].posy[0] + bone_army_1[i].veloy, bone_army_1[i].posy); 
                update_pos(bone_army_2[i].posx[0] + bone_army_2[i].velox, bone_army_2[i].posx); 

                draw_bone(&bone_army_1[i], 0, 0xffff, bounds_default); //draw new one
                draw_bone_h(&bone_army_2[i], 0, 0xffff, bounds_default); //draw new one
            }
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;

        }
    }

    { // bottom right bone
        int frameCount = 0;
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap player to bottom
            if (player1.posy[0] < player1.ground) {
                player1.posy[0] += 4 << 8;
                if (player1.posy[0] > player1.ground) {player1.posy[0] = player1.ground;}
            }
            // snap right
            if (player1.posx[0] < (player1.bounds[2] - 5) << 8) {
                player1.posx[0] += 4 << 8;
                if (player1.posx[0] > (player1.bounds[2] - 5) << 8) {player1.posx[0] = (player1.bounds[2] - 5) << 8;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0; // reset frameCount

        // substage0-1: red lines
        while (1) {

            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            draw_rectangle_outline(124, 166, 198, 191, 0xf800);
            draw_rectangle_outline(173, 117, 198, 191, 0xf800);
            swap_buffers();
            frameCount++;
        }

        frameCount = 0;
        // default bound is {123, 116, 199, 192}
        draw_rectangle_outline(124, 166, 198, 191, 0x0000);
        draw_rectangle_outline(173, 117, 198, 191, 0x0000);
        swap_buffers();
        draw_rectangle_outline(124, 166, 198, 191, 0x0000);
        draw_rectangle_outline(173, 117, 198, 191, 0x0000);

        // substage1: bottom bone
        struct Bone bone_army_1[20];
        struct Bone bone_army_2[20];
        for (int i = 0; i < 20; i++) {
            bone_army_1[i].posx[0] = 203 << 8;
            bone_army_1[i].posx[1] = 203 << 8;
            bone_army_1[i].posx[2] = 203 << 8;
            bone_army_1[i].posy[0] = (116 + 7*i) << 8;
            bone_army_1[i].posy[1] = (116 + 7*i) << 8;
            bone_army_1[i].posy[2] = (116 + 7*i) << 8;
            bone_army_1[i].length = 30;
            bone_army_1[i].velox = -2048;
            bone_army_1[i].veloy = 0;
            bone_army_1[i].color = 0xFFFF;
        }

        for (int i = 0; i < 20; i++) {
            bone_army_2[i].posx[0] = (199 - 7 * i) << 8;
            bone_army_2[i].posx[1] = (199 - 7 * i )<< 8;
            bone_army_2[i].posx[2] = (199 - 7 * i )<< 8;
            bone_army_2[i].posy[0] = 196 << 8;
            bone_army_2[i].posy[1] = 196 << 8;
            bone_army_2[i].posy[2] = 196 << 8;
            bone_army_2[i].length = 30;
            bone_army_2[i].velox = 0;
            bone_army_2[i].veloy = -2048;
            bone_army_2[i].color = 0xFFFF;
        }

        while (1) {
            
            if (frameCount > 60) {
                break;
            }

            for (int i = 0; i < 20; i++) {
                draw_bone_h(&bone_army_1[i], 1, 0x0000, bounds_default); //erase old one
                draw_bone(&bone_army_2[i], 1, 0x0000, bounds_default); //erase old one
            }

            draw_player(&player1, 1, 0x0000);

            for (int i = 0; i < 20; i++) {
                if(bone_army_1[i].posx[0] <= 173 << 8) {
                    bone_army_1[i].velox = 0;
                }
                if (frameCount > 55) {
                    bone_army_1[i].velox = 2048;
                }

                if(bone_army_2[i].posy[0] <= 166 << 8) {
                    bone_army_2[i].veloy = 0;
                }
                if (frameCount > 55) {
                    bone_army_2[i].veloy = 2048;
                }


                update_pos(bone_army_1[i].posx[0] + bone_army_1[i].velox, bone_army_1[i].posx); 
                update_pos(bone_army_2[i].posy[0] + bone_army_2[i].veloy, bone_army_2[i].posy); 

                draw_bone_h(&bone_army_1[i], 0, 0xffff, bounds_default); //draw new one
                draw_bone(&bone_army_2[i], 0, 0xffff, bounds_default); //draw new one
            }
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;

        }
    }

    {
    // left bone
        int frameCount = 0;
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap
            if (player1.posx[0] > (player1.bounds[0]) << 8) {
                player1.posx[0] -= 4 << 8;
                if (player1.posx[0] < (player1.bounds[0]) << 8) {player1.posx[0] = (player1.bounds[0]) << 8;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0; // reset frameCount

        // substage0-1: red lines
        while (1) {

            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            // default bound is {123, 116, 199, 192}
            draw_rectangle_outline(124, 117, 150, 191, 0xf800);
            swap_buffers();
            frameCount++;
        }

        frameCount = 0;
        draw_rectangle_outline(124, 117, 150, 191, 0x0000);
        swap_buffers();
        draw_rectangle_outline(124, 117, 150, 191, 0x0000);

        // left bone
        struct Bone bone_army_1[20];
        for (int i = 0; i < 20; i++) {
            bone_army_1[i].posx[0] = 83 << 8;
            bone_army_1[i].posx[1] = 83 << 8;
            bone_army_1[i].posx[2] = 83 << 8;
            bone_army_1[i].posy[0] = (116 + 7*i) << 8;
            bone_army_1[i].posy[1] = (116 + 7*i) << 8;
            bone_army_1[i].posy[2] = (116 + 7*i) << 8;
            bone_army_1[i].length = 30;
            bone_army_1[i].velox = 2048;
            bone_army_1[i].veloy = 0;
            bone_army_1[i].color = 0xFFFF;
        }

        while (1) {
            
            if (frameCount > 60) {
                break;
            }

            for (int i = 0; i < 20; i++) {
                draw_bone_h(&bone_army_1[i], 1, 0x0000, bounds_default); //erase old one
            }

            draw_player(&player1, 1, 0x0000);

            for (int i = 0; i < 20; i++) {
                if(bone_army_1[i].posx[0] >= 113 << 8) {
                    bone_army_1[i].velox = 0;
                }
                if (frameCount > 55) {
                    bone_army_1[i].velox = -2048;
                }

                update_pos(bone_army_1[i].posx[0] + bone_army_1[i].velox, bone_army_1[i].posx); 

                draw_bone_h(&bone_army_1[i], 0, 0xffff, bounds_default); //draw new one
            }
            movement(&player1, NULL, 0);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);
            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;

        }
    }

    // algorithm given by Gemini
    // default bound is {123, 116, 199, 192}
    int cx = 160;     
    int cy = 154;      
    int radius = 80; 

    int num_blasters = 103;
    struct blaster final_attack[103];

    for (int i = 0; i < num_blasters; i++) {
        int spawn_angle = 3600 - (i * 15);
        
        int lut_index = spawn_angle % 360;

        final_attack[i].centerx = cx + ((radius * cosValues[lut_index]) >> 8);
        final_attack[i].centery = cy + ((radius * sinValues[lut_index]) >> 8);
        
        final_attack[i].rotation = (lut_index + 90) % 360;
        
        final_attack[i].frameCount = -(i * 5); 
    }

    frameCount = 0;

    while (1) {
        erase_head(&head);
        erase_sans(&sans);
        if (frameCount > 580){ break; }

        draw_player(&player1, 1, 0x0000);
    
		if (player1.health == 0) {return 1;}

 		for (int i = 0; i < num_blasters; i++) {
			draw_any_thin_blaster(&final_attack[i], bounds_unlimited);
            // draw_sans(&sans, bounds_unlimited);
            // draw_head(&head, bounds_unlimited);
		}
		
        movement(&player1, NULL, 0);
        draw_player(&player1, 0, 0xf800);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);

        draw_rectangle(120, 113, 202, 115, 0xFFFF, bounds_unlimited);
        draw_rectangle(120, 113, 122, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(120, 193, 202, 195, 0xFFFF, bounds_unlimited);
        draw_rectangle(200, 113, 202, 195, 0xFFFF, bounds_unlimited);

        
        swap_buffers();
        frameCount++;
    }

    frameCount = 0;

    for (int i = 0; i < 6; i++) {
        // snap left
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap left
            if (player1.posx[0] > (player1.bounds[0]) << 8) {
                player1.posx[0] -= 4 << 8;
                if (player1.posx[0] < (player1.bounds[0]) << 8) {player1.posx[0] = (player1.bounds[0]) << 8;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0;

        // snap right
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap
            if (player1.posx[0] < (player1.bounds[2] - 5) << 8) {
                player1.posx[0] += 4 << 8;
                if (player1.posx[0] > (player1.bounds[2] - 5) << 8) {player1.posx[0] = (player1.bounds[2] - 5) << 8;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0;

        // snap up
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap player to bottom
            if (player1.posy[0] > (player1.bounds[1] << 8)) {
                player1.posy[0] -= 4 << 8;
                if (player1.posy[0] < (player1.bounds[1] << 8)) {player1.posy[0] = (player1.bounds[1] << 8);}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0;

        // snap down
        sans.centerx = 161;
        sans.centery = 83;
        while (1) {
            //draw_sans(&sans, bounds_unlimited);
            //draw_sleeping_head(&head, bounds_unlimited);
            //draw_z(&z, bounds_unlimited);
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap player to bottom
            if (player1.posy[0] < player1.ground) {
                player1.posy[0] += 4 << 8;
                if (player1.posy[0] > player1.ground) {player1.posy[0] = player1.ground;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        frameCount = 0;

        // snap left
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap left
            if (player1.posx[0] > (player1.bounds[0]) << 8) {
                player1.posx[0] -= 4 << 8;
                if (player1.posx[0] < (player1.bounds[0]) << 8) {player1.posx[0] = (player1.bounds[0]) << 8;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        // snap up
        frameCount = 0;
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap player to bottom
            if (player1.posy[0] > (player1.bounds[1] << 8)) {
                player1.posy[0] -= 4 << 8;
                if (player1.posy[0] < (player1.bounds[1] << 8)) {player1.posy[0] = (player1.bounds[1] << 8);}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        // snap right
        frameCount = 0;
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap
            if (player1.posx[0] < (player1.bounds[2] - 5) << 8) {
                player1.posx[0] += 4 << 8;
                if (player1.posx[0] > (player1.bounds[2] - 5) << 8) {player1.posx[0] = (player1.bounds[2] - 5) << 8;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }

        // snap down
        frameCount = 0;
        while (1) {
            if (frameCount > 20) {
                break;
            }

            draw_player(&player1, 1, 0x0000);
            movement(&player1, NULL, 0);
            // snap player to bottom
            if (player1.posy[0] < player1.ground) {
                player1.posy[0] += 4 << 8;
                if (player1.posy[0] > player1.ground) {player1.posy[0] = player1.ground;}
            }
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);
            draw_healthbar(player1.health);
            draw_player(&player1, 0, 0xf800);

            if (player1.health == 0) {return 1;}

            swap_buffers();
            frameCount++;
        }
        
    }
    sans.centerx = 161;
    sans.centery = 83;
    head.centerx = 161;
    head.centery = 83;
    draw_sans(&sans, bounds_unlimited);
    draw_sleeping_head(&head, bounds_unlimited);
    draw_z(&z, bounds_unlimited);
    swap_buffers();
    *Global_health = player1.health;
    audio_stop();

    while (1) {

        draw_player(&player1, 1, 0x0000);
        movement(&player1, NULL, 0);
        draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
        draw_number(0,0,player1.health/10);
        draw_number(12,0,player1.health%10);
        draw_healthbar(player1.health);
        draw_player(&player1, 0, 0xf800);

        if (player1.health == 0) {return 1;}
        sans.centerx = 161;
        sans.centery = 83;
        head.centerx = 161;
        head.centery = 83;
        draw_sans(&sans, bounds_unlimited);
        draw_sleeping_head(&head, bounds_unlimited);
        draw_z(&z, bounds_unlimited);
        swap_buffers();
    }

}