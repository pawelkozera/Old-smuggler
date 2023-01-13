#include "movingspeed.h"


long double MovingSpeed::x_speed = 3;
long double MovingSpeed::y_speed = 3;

int MovingSpeed::current_power = 20;
double MovingSpeed::current_speed = 0;

const int MovingSpeed::division_power_factor_index = 20;
const int MovingSpeed::max_power = 200;
const double MovingSpeed::division_factor_speed = 40;
const int MovingSpeed::max_speed[12] = {
    -30,
    0,
    30,
    60,
    90,
    120,
    150,
    180,
    210,
    240,
    270,
    300
};
