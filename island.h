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

    void move_island_event(QKeyEvent *event, int x_speed = MovingSpeed::x_speed, int y_speed = MovingSpeed::y_speed);
    void move_island(int x_speed, int y_speed);
    void move_objects_on_island(int x, int y);
};

#endif // ISLAND_H
