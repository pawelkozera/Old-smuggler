#ifndef ISLAND_H
#define ISLAND_H

#include "interactiveobject.h"
#include "movingspeed.h"

#include <QPainter>
#include <QGraphicsItem>


class Island
{
public:
    Island(QString img_name);
    bool is_visible;
    QPixmap island_img;
    QGraphicsPixmapItem *island_item;
    std::vector<InteractiveObject *> objects;

    void move_island_event(QKeyEvent *event, long double x_speed = MovingSpeed::x_speed, long double y_speed = MovingSpeed::y_speed);
    void move_island(long double x_speed, long double y_speed);
    void move_objects_on_island(long double x, long double y);
};

#endif // ISLAND_H
