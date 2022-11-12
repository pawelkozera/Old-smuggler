#ifndef INTERFACE_H
#define INTERFACE_H

#include <QGraphicsItem>

class Interface
{
public:
    Interface();

    QPixmap blank_img;
    QPixmap speedometer_img;
    QGraphicsPixmapItem *speedometer_item;
    QGraphicsTextItem *power;
    QGraphicsTextItem *speed;

    void draw_speedometer(int window_height, bool blank = true);
};

#endif // INTERFACE_H
