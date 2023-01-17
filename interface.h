#ifndef INTERFACE_H
#define INTERFACE_H

#include "playerplane.h"
#include <QGraphicsItem>


///Klasa interfejsu
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

    /*!Funkcja pobiera wysokość okna i wskaźnik samolotu gracza; zwraca nic*/
    void draw_cockpit(int window_height, PlayerPlane const *player_plane);
    /*!Funkcja pobiera nic; zwraca nic*/
    void draw_map();
    /*!Funkcja pobiera nic; zwraca nic*/
    void draw_can();
};

#endif // INTERFACE_H
