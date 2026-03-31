#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "graphics.h"
#include "stage_0.h"
#include "stage_2.h"
#include "stage_3.h"
#include "stage_4.h"
#include "stage_5.h"
#include "stage_6.h"
#include "stage_7.h"
#include "stage_8.h"
#include "stage_9.h"
#include "stage_10.h"
#include "stage11.h"
#include "stage12.h"
#include "stage13.h"
#include "stage14.h"
#include "stage15a.h"
#include "stage15b.h"
#include "stage16a.h"
#include "stage16b.h"
#include "stage17a.h"
#include "stage17b.h"
#include "stage18a.h"
#include "stage18b.h"
#include "stage19.h"
#include "stage20.h"
#include "movement.h"


int main(void)
{
    restart_label:
    


    while (1) {
        int start = start_check();
        if (start) {
            break;
        }
    }


    int bounds_unlimited[4] = {0, 0, 319, 239};


    int Global_health = 99;

    stage_0_label:
    int death = run_stage_0(&Global_health);
    break_code = false;
    up_pressed = false;
    left_pressed = false;
    right_pressed = false;
    down_pressed = false;

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        goto restart_label;
    } else if (death == 3) { // heal
        goto stage_2_label;
    }
    
    // audio_init();

    stage_2_label:
    death = 0;
    death = run_stage_2(&Global_health);
    break_code = false;
    up_pressed = false;
    left_pressed = false;
    right_pressed = false;
    down_pressed = false;

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        goto restart_label;
    } else if (death == 3) { // heal
        goto stage_2_label;
    }

    stage_3_label:
    death = 0;
    death = run_stage_3(&Global_health);
    break_code = false;
    up_pressed = false;
    left_pressed = false;
    right_pressed = false;
    down_pressed = false;

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        goto restart_label;
    } else if (death == 3) { // heal
        goto stage_3_label;
    }

    stage_4_label:
    death = 0;
    death = run_stage_4(&Global_health);
    break_code = false;
    up_pressed = false;
    left_pressed = false;
    right_pressed = false;
    down_pressed = false;

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        goto restart_label;
    } else if (death == 3) { // heal
        goto stage_4_label;
    }

    stage_5_label:
    death = 0;
    death = run_stage_5(&Global_health);
    break_code = false;
    up_pressed = false;
    left_pressed = false;
    right_pressed = false;
    down_pressed = false;

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        goto restart_label;
    } else if (death == 3) { // heal
        goto stage_5_label;
    }
    
    stage_6_label:
    death = 0;
    death = run_stage_6(&Global_health);
    break_code = false;
    up_pressed = false;
    left_pressed = false;
    right_pressed = false;
    down_pressed = false;

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        goto restart_label;
    } else if (death == 3) { // heal
        goto stage_6_label;
    }
    
    stage_7_label:
    death = 0;
    death = run_stage_7(&Global_health);
    break_code = false;
    up_pressed = false;
    left_pressed = false;
    right_pressed = false;
    down_pressed = false;

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        goto restart_label;
    } else if (death == 3) { // heal
        goto stage_7_label;
    }
    
    stage_8_label:
    death = 0;
    death = run_stage_8(&Global_health);
    break_code = false;
    up_pressed = false;
    left_pressed = false;
    right_pressed = false;
    down_pressed = false;

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        goto restart_label;
    } else if (death == 3) { // heal
        goto stage_8_label;
    }
    
    stage_9_label:
    death = 0;
    death = run_stage_9(&Global_health);
    break_code = false;
    up_pressed = false;
    left_pressed = false;
    right_pressed = false;
    down_pressed = false;

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        goto restart_label;
    } else if (death == 3) { // heal
        goto stage_9_label;
    }
    
    stage_10_label:
    death = 0;
    death = run_stage_10(&Global_health);
    break_code = false;
    up_pressed = false;
    left_pressed = false;
    right_pressed = false;
    down_pressed = false;

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        goto restart_label;
    } else if (death == 3) { // heal
        goto stage_10_label;
    }

    

    int count = 0;
    death = 0;

    while (1) {
        if (count > 8) {
            break;
        }
        multistage_label:
        for (int i = 0; i < 4; i++) {
            int value = rand() % (13);
            if (value == 0) {
                death = run_stage_17a(&Global_health);
            } else if (value == 1) {
                death = run_stage_11(&Global_health);
            } else if (value == 2) {
                death = run_stage_12(&Global_health);
            } else if (value == 3) {
                death = run_stage_13(&Global_health);
            } else if (value == 4) {
                death = run_stage_14(&Global_health);
            } else if (value == 5) {
                death = run_stage_15a(&Global_health);
            } else if (value == 6) {
                death = run_stage_15b(&Global_health);
            } else if (value == 7) {
                death = run_stage_16a(&Global_health);
            } else if (value == 8) {
                death = run_stage_16b(&Global_health);
            } else if (value == 9) {
                death = run_stage_17a(&Global_health);
            } else if (value == 10) {
                death = run_stage_17b(&Global_health);
            } else if (value == 11) {
                death = run_stage_18a(&Global_health);
            } else if (value == 12) {
                death = run_stage_18b(&Global_health);
            }
            if (death == 1) { // playear is dead
                clear_screen(); 
                swap_buffers(); 
                
                clear_screen(); 
                swap_buffers();

                goto restart_label;
            }
            break_code = false;
            up_pressed = false;
            left_pressed = false;
            right_pressed = false;
            down_pressed = false;
        }

        struct player player1;
        player1.ground = (192 - 5) << 8;
        for (int i = 0; i < 3; i++) {
            player1.posx[i] = 160 << 8;
            player1.posy[i] = 120 << 8;
        }
        player1.was_up_pressed = false;
        player1.have_gravity = false;
        
        for (int i = 0; i< 4; i++) {
            player1.bounds[i] = bounds_unlimited[i];
        }
        player1.health = Global_health;
        player1.gravity = 8;
        player1.veloY = 0;
        player1.burst_force = 400;

        clear_screen();
        swap_buffers();
        clear_screen();

        while (1) {

            draw_player(&player1, 1, 0x0000);
            int result = interstage_movement(&player1);
            draw_player(&player1, 0, 0xf800);
            draw_rectangle(0,0, 30, 20, 0x0000, bounds_unlimited);
            draw_number(0,0,player1.health/10);
            draw_number(12,0,player1.health%10);

            draw_fight_button(100, 180);
            draw_iteam_button(200, 180);

            if (result == 2) { // fight
                count++;
                break;
            } else if (result == 3) {
                Global_health += 99;
                if (Global_health > 99) {Global_health = 99;}
                break; // player chooses to heal
            }

            swap_buffers();
        }
    }
	
	stage_19_label:
        death = 0;
        death = run_stage_19(&Global_health);
        break_code = false;
        up_pressed = false;
        left_pressed = false;
        right_pressed = false;
        down_pressed = false;

        if (death == 1) { // playear is dead
            clear_screen(); 
            swap_buffers(); 
            
            clear_screen(); 
            swap_buffers();

            goto restart_label;
        } else if (death == 3) { // heal
            goto stage_19_label;
        }



    death = 0;
        death = run_stage_20(&Global_health);

        if (death == 1) { // playear is dead
            clear_screen(); 
            swap_buffers(); 
            
            clear_screen(); 
            swap_buffers();

            goto restart_label;
        }
    
    
}