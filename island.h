#ifndef ISLAND_H
#define ISLAND_H

#include "interactiveobject.h"
#include "movingspeed.h"
#include "antiaircraftgun.h"

#include <QPainter>
#include <QGraphicsItem>


class Island
{
public:
    Island(QString img_name);
    QPixmap island_img;
    QGraphicsPixmapItem *island_item;
    std::vector<InteractiveObject *> objects;
    bool target_island;
    int x_starting, y_starting;
    AntiAircraftGun *antiAircraftGun;

    void move_island_event(QKeyEvent *event, long double x_speed = MovingSpeed::x_speed, long double y_speed = MovingSpeed::y_speed);
    void move_island(long double x_speed, long double y_speed);
    void move_objects_on_island(long double x, long double y);
    void move_antiaircraftgun(long double x, long double y);
};

#endif // ISLAND_H
