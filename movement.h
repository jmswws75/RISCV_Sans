#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <stdbool.h>

struct player{
    int posx[3];
    int posy[3];
    int bounds[4];

    int ground;
    int health;

    bool have_gravity;
    bool was_up_pressed;
    
    int veloY;
    int gravity;
    // gravity, its working against me...
    // gravity, wants to bring me down
    // I'll never know
    // what makes a man
    // of all the love his heart can stand
    // dream of ways to throw it all away...
    int burst_force;
    
};

#endif
