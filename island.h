#ifndef ISLAND_H
#define ISLAND_H

#include "interactiveobject.h"
#include "movingspeed.h"
#include "antiaircraftgun.h"

#include <QPainter>
#include <QGraphicsItem>


///Klasa wyspy
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

    /*!Funkcja pobiera wskaźnik zdarzenia i parametry prędkości; zwraca nic*/
    void move_island_event(QKeyEvent *event, long double x_speed = MovingSpeed::x_speed, long double y_speed = MovingSpeed::y_speed);
    /*!Funkcja pobiera parametry prędkości; zwraca nic*/
    void move_island(long double x_speed, long double y_speed);
    /*!Funkcja pobiera pozycję obiektu na wyspie; zwraca nic*/
    void move_objects_on_island(long double x, long double y);
    /*!Funkcja pobiera pozycję działka przeciwlotniczego; zwraca nic*/
    void move_antiaircraftgun(long double x, long double y);
};

#endif // ISLAND_H
