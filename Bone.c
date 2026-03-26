#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "graphics.h"
#include "stage_0.h"


int main(void)
{
    int Global_health = 99;
    int death = run_stage_0();

    if (death == 1) {
        clear_screen(); 
        swap_buffers(); 
        
        clear_screen(); 
        swap_buffers();
    }
    
}
