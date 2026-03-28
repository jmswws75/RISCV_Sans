#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "graphics.h"
#include "stage_0.h"


int main(void)
{
    int Global_health = 99;

    stage_0_label:
    int death = run_stage_0(&Global_health);

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        return 0;
    } else if (death == 3) { // heal
        goto stage_0_label;
    }

    stage_2_label:
    death = 0;
    death = run_stage_2(&Global_health);

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        return 0;
    } else if (death == 3) { // heal
        goto stage_2_label;
    }

    stage_3_label:
    death = 0;
    death = run_stage_3(&Global_health);

    if (death == 1) { // playear is dead
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();

        return 0;
    } else if (death == 3) { // heal
        goto stage_3_label;
    }
    
}
