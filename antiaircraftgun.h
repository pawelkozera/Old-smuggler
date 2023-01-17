#ifndef ANTIAIRCRAFTGUN_H
#define ANTIAIRCRAFTGUN_H

#include <QGraphicsItem>
#include <QList>
#include <cmath>

#include "bullet.h"
#include "settings.h"
#include "cloud.h"
#include "sounds.h"


///Klasa działek przeciwlotniczych
class AntiAircraftGun
{
public:
    AntiAircraftGun(QString img_name, Settings *settings, int amount_of_bullets);

    QPixmap img;
    QGraphicsPixmapItem *item;
    float range;
    float rotation_angle;
    std::vector<Bullet *> bullets;
    std::vector<Bullet *> used_bullets;
    int delay;
    int current_delay;

    /*!Funkcja pobiera wskaźnik na samolot gracza; zwraca true/false*/
    bool is_in_range(QGraphicsPixmapItem *playerPlaneItem);
    /*!Funkcja pobiera rozmiary okna gry; zwraca nic*/
    void rotate(int window_width, int window_height);
    /*!Funkcja pobiera wskaźnik samolotu wroga, strukturę vector chmur, dźwięki ; zwraca nic*/
    void shoot(QGraphicsPixmapItem *plane, QList<Cloud*> clouds, Sounds *sounds);
    /*!Funkcja pobiera nic; zwraca nic*/
    void move_used_bullets();
    /*!Funkcja pobiera wskaźnik trafienia gracza, wskaźnik życia gracza, wskaźnik paliwa gracza; zwraca nic*/
    void check_used_bullets_collision(QGraphicsPixmapItem *target, int *target_hp, bool *target_fuel);
    /*!Funkcja pobiera wskaźnik samolotu wroga, strukturę vector chmur; zwraca true/false*/
    bool is_in_cloud(QGraphicsPixmapItem *plane, QList<Cloud*> clouds);
};

#endif // ANTIAIRCRAFTGUN_H
