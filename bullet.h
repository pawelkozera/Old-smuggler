#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <cmath>

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

    void move_bullet();
    void set_params(float rotation_angle);
    void calculate_x_y_speed();
    bool out_of_range();
    bool collision(QGraphicsPixmapItem *target);
};

#endif // BULLET_H
