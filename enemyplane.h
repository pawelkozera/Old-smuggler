#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "antiaircraftgun.h"
#include "movingspeed.h"
#include "playerplane.h"

#include <QKeyEvent>

class EnemyPlane : public AntiAircraftGun
{
public:
    EnemyPlane(QString img_name, Settings *settings, int amount_of_bullets);

    int index;
    int x1, y1;
    int x2, y2;
    int speed;

    void move_plane_event(QKeyEvent *event, long double x_speed = MovingSpeed::x_speed, long double y_speed = MovingSpeed::y_speed);
    void move_plane(long double x_speed, long double y_speed);
    void follow_player(int window_width, int window_height, PlayerPlane *playerPlane);
    void move_to_point();
};

#endif // ENEMYPLANE_H
