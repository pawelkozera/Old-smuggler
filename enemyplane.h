#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "antiaircraftgun.h"
#include "movingspeed.h"
#include "playerplane.h"

#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

class EnemyPlane : public AntiAircraftGun
{
public:
    EnemyPlane(QString img_name, Settings *settings, int amount_of_bullets);

    int index;
    std::vector<long double> x_points;
    std::vector<long double> y_points;
    int speed;

    void move_plane_event(QKeyEvent *event, long double x_speed = MovingSpeed::x_speed, long double y_speed = MovingSpeed::y_speed);
    void move_plane(long double x_speed, long double y_speed);
    void follow_player(int window_width, int window_height, PlayerPlane *playerPlane);
    void move_to_point();
};

#endif // ENEMYPLANE_H
