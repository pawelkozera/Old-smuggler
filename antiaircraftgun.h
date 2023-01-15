#ifndef ANTIAIRCRAFTGUN_H
#define ANTIAIRCRAFTGUN_H

#include <QGraphicsItem>
#include <QList>
#include <cmath>

#include "bullet.h"
#include "settings.h"
#include "cloud.h"

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

    bool is_in_range(QGraphicsPixmapItem *playerPlaneItem);
    void rotate(int window_width, int window_height);
    void shoot(QGraphicsPixmapItem *plane, QList<Cloud*> clouds);
    void move_used_bullets();
    void check_used_bullets_collision(QGraphicsPixmapItem *target, int *target_hp, bool *target_fuel);
    bool is_in_cloud(QGraphicsPixmapItem *plane, QList<Cloud*> clouds);
};

#endif // ANTIAIRCRAFTGUN_H
