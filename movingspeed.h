#ifndef MOVINGSPEED_H
#define MOVINGSPEED_H


class MovingSpeed
{
public:
    static long double x_speed;
    static long double y_speed;

    static int current_power;
    static double current_speed;

    const static int division_power_factor_index;
    const static int max_power;
    const static double division_factor_speed;
    const static int max_speed[];
};

#endif // MOVINGSPEED_H
