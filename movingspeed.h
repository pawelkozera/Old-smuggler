#ifndef MOVINGSPEED_H
#define MOVINGSPEED_H


class MovingSpeed
{
public:
    static int x_speed;
    static int y_speed;

    static int current_power;
    static int current_speed;

    const static int division_power_factor_index;
    const static float division_factor_speed;
    const static int max_speed[];
};

#endif // MOVINGSPEED_H
