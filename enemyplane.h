#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H

#include "antiaircraftgun.h"
#include "movingspeed.h"
#include "playerplane.h"

#include <QKeyEvent>
#include <QPropertyAnimation>
#include <QGraphicsItemAnimation>
#include <QTimeLine>


///Klasa samolotu wroga
class EnemyPlane : public AntiAircraftGun
{
public:
    EnemyPlane(QString img_name, Settings *settings, int amount_of_bullets);

    int index;
    std::vector<long double> x_points;
    std::vector<long double> y_points;
    int speed;

    /*!Funkcja pobiera wskaźnik zdarzenia, i parametry prędkości; zwraca nic*/
    void move_plane_event(QKeyEvent *event, long double x_speed = MovingSpeed::x_speed, long double y_speed = MovingSpeed::y_speed);
    /*!Funkcja pobiera parametry prędkości; zwraca nic*/
    void move_plane(long double x_speed, long double y_speed);
    /*!Funkcja pobiera wymiary okna gry i wskaźnik samolotu gracza; zwraca nic*/
    void follow_player(int window_width, int window_height, PlayerPlane *playerPlane);
    /*!Funkcja pobiera nic; zwraca nic*/
    void move_to_point();
    /*!Funkcja pobiera wskaźnik samolotu gracza; zwraca true/false*/
    bool collision_with_player_plane(PlayerPlane *playerPlane);
};

#endif // ENEMYPLANE_H
