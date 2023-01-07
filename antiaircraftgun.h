#ifndef ANTIAIRCRAFTGUN_H
#define ANTIAIRCRAFTGUN_H

#include <QGraphicsItem>
#include <cmath>

#include "bullet.h"
#include "settings.h"

class AntiAircraftGun
{
public:
    AntiAircraftGun(QString img_name, Settings *settings);

    QPixmap img;
    QGraphicsPixmapItem *item;
    float range;
    float rotation_angle;
    std::vector<Bullet *> bullets;
    std::vector<Bullet *> used_bullets;
    int delay;
    int current_delay;

    bool is_in_range(int window_width, int window_height);
    void rotate(int window_width, int window_height);
    void shoot();
    void move_used_bullets();
    void check_used_bullets_collision(QGraphicsPixmapItem *target);
};

#endif // ANTIAIRCRAFTGUN_H
