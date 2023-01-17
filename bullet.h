#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <cmath>


///Klasa pocisku
class Bullet
{
public:
    Bullet(QString img_name);

    QPixmap img;
    QGraphicsPixmapItem *item;
    float speed;
    float x_speed;
    float y_speed;
    float angle;
    float max_range;
    float x_start;
    float y_start;

    /*!Funkcja pobiera nic; zwraca nic*/
    void move_bullet();
    /*!Funkcja pobiera parametr kąta obrotu; zwraca nic*/
    void set_params(float rotation_angle);
    /*!Funkcja pobiera nic; zwraca nic*/
    void calculate_x_y_speed();
    /*!Funkcja pobiera nic; zwraca true/false*/
    bool out_of_range();
    /*!Funkcja pobiera; zwraca true/false*/
    bool collision(QGraphicsPixmapItem *target);
};

#endif // BULLET_H
