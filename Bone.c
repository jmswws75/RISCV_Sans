#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "graphics.h"
#include "stage_0.h"


int main(void)
{
    { // normal stages
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

        stage_4_label:
        death = 0;
        death = run_stage_4(&Global_health);

        if (death == 1) { // playear is dead
            clear_screen(); 
            swap_buffers(); 
            
            clear_screen(); 
            swap_buffers();

            return 0;
        } else if (death == 3) { // heal
            goto stage_4_label;
        }

        stage_5_label:
        death = 0;
        death = run_stage_5(&Global_health);

        if (death == 1) { // playear is dead
            clear_screen(); 
            swap_buffers(); 
            
            clear_screen(); 
            swap_buffers();

            return 0;
        } else if (death == 3) { // heal
            goto stage_5_label;
        }
		
		stage_6_label:
        death = 0;
        death = run_stage_6(&Global_health);

        if (death == 1) { // playear is dead
            clear_screen(); 
            swap_buffers(); 
            
            clear_screen(); 
            swap_buffers();

            return 0;
        } else if (death == 3) { // heal
            goto stage_6_label;
        }
		
		stage_7_label:
        death = 0;
        death = run_stage_7(&Global_health);

        if (death == 1) { // playear is dead
            clear_screen(); 
            swap_buffers(); 
            
            clear_screen(); 
            swap_buffers();

            return 0;
        } else if (death == 3) { // heal
            goto stage_7_label;
        }
		
		stage_8_label:
        death = 0;
        death = run_stage_8(&Global_health);

        if (death == 1) { // playear is dead
            clear_screen(); 
            swap_buffers(); 
            
            clear_screen(); 
            swap_buffers();

            return 0;
        } else if (death == 3) { // heal
            goto stage_8_label;
        }
		
		stage_9_label:
        death = 0;
        death = run_stage_9(&Global_health);

        if (death == 1) { // playear is dead
            clear_screen(); 
            swap_buffers(); 
            
            clear_screen(); 
            swap_buffers();

            return 0;
        } else if (death == 3) { // heal
            goto stage_9_label;
        }
		
		stage_10_label:
        death = 0;
        death = run_stage_10(&Global_health);

        if (death == 1) { // playear is dead
            clear_screen(); 
            swap_buffers(); 
            
            clear_screen(); 
            swap_buffers();

            return 0;
        } else if (death == 3) { // heal
            goto stage_10_label;
        }

    }
    
}
