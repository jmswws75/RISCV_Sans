#ifndef MOVEMENT_H
#define MOVEMENT_H

struct player{
    int rise_speed;
    int fall_speed;
    int ground;
    int max_height;
    int posx[3];
    int posy[3];
    int start_y;
    bool was_up_pressed;
    bool force_fall;
    bool have_gravity;
    int bounds[4];
    int health;
};

#endif