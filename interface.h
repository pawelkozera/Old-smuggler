#ifndef INTERFACE_H
#define INTERFACE_H

#include "playerplane.h"
#include <QGraphicsItem>

class Interface
{
public:
    Interface();

    QPixmap cockpit_img;
    QGraphicsPixmapItem *cockpit_item;
    QGraphicsTextItem *power;
    QGraphicsTextItem *speed;
    QGraphicsTextItem *fuel;
    QGraphicsTextItem *cargo;

    QPixmap map_img;
    QGraphicsPixmapItem *map_item;
    QGraphicsTextItem *key_to_draw_map;
    QGraphicsTextItem *key_to_draw_score;

    QPixmap can_img;
    QGraphicsPixmapItem *can_item;


    void draw_cockpit(int window_height, PlayerPlane const *player_plane);
    void draw_map();
    void draw_can();
};

#endif // INTERFACE_H
