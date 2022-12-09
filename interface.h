#ifndef INTERFACE_H
#define INTERFACE_H

#include <QGraphicsItem>

class Interface
{
public:
    Interface();

    QPixmap speedometer_img;
    QGraphicsPixmapItem *speedometer_item;
    QGraphicsTextItem *power;
    QGraphicsTextItem *speed;

    QPixmap map_img;
    QGraphicsPixmapItem *map_item;
    QGraphicsTextItem *key_to_draw_map;


    void draw_speedometer(int window_height);
    void draw_map();
};

#endif // INTERFACE_H
