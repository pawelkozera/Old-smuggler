#ifndef MOVINGSPEED_H
#define MOVINGSPEED_H


class MovingSpeed
{
public:
    static int x_speed;
    static int y_speed;

    static int fuel;
    static int cargo;

    static int current_power;
    static int current_speed;
    const static int power[];
    const static int max_speed[];
};

#endif // MOVINGSPEED_H
