#ifndef MOVINGSPEED_H
#define MOVINGSPEED_H


class MovingSpeed
{
public:
    static float x_speed;
    static float y_speed;

    static int current_power;
    static float current_speed;

    const static int division_power_factor_index;
    const static int max_power;
    const static float division_factor_speed;
    const static int max_speed[];
};

#endif // MOVINGSPEED_H
