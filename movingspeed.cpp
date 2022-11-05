#include "movingspeed.h"


int MovingSpeed::x_speed = 3;
int MovingSpeed::y_speed = 3;

int MovingSpeed::fuel = 0;
int MovingSpeed::cargo = 0;

int MovingSpeed::current_power = 0;
int MovingSpeed::current_speed = 0;
const int MovingSpeed::power[11] = {
    0,
    10,
    20,
    30,
    40,
    50,
    60,
    70,
    80,
    90,
    100
};
const int MovingSpeed::max_speed[11] = {
    0,
    10,
    20,
    25,
    30,
    35,
    40,
    45,
    50,
    55,
    60
};
