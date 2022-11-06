#include "movingspeed.h"


int MovingSpeed::x_speed = 3;
int MovingSpeed::y_speed = 3;

int MovingSpeed::current_power = 0;
int MovingSpeed::current_speed = 0;

const int MovingSpeed::division_power_factor_index = 10;
const float MovingSpeed::division_factor_speed = 40;
const int MovingSpeed::max_speed[11] = {
    0,
    60,
    120,
    180,
    240,
    300,
    360,
    420,
    480,
    540,
    600
};
