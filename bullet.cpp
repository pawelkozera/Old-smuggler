#include "bullet.h"
#include "movingspeed.h"

Bullet::Bullet(QString img_name) {
    img.load("../smuggler/assets/objects/" + img_name);
    speed = 6;
    x_speed = y_speed = 1;
    max_range = 1000;
}

void Bullet::move_bullet() {
    if (angle >= 0 && angle <= 90)
        item->setPos(item->x() - x_speed + MovingSpeed::x_speed, item->y() + y_speed + MovingSpeed::y_speed);
    else if (angle > 90 && angle <= 180)
        item->setPos(item->x() + x_speed + MovingSpeed::x_speed, item->y() + y_speed + MovingSpeed::y_speed);
    else if (angle > 180 && angle <= 270)
        item->setPos(item->x() + x_speed + MovingSpeed::x_speed, item->y() - y_speed + MovingSpeed::y_speed);
    else
        item->setPos(item->x() - x_speed + MovingSpeed::x_speed, item->y() - y_speed + MovingSpeed::y_speed);
}

void Bullet::set_params(float rotation_angle) {
    item->setRotation(rotation_angle);
    angle = -rotation_angle;
    x_start = item->x();
    y_start = item->y();
}

void Bullet::calculate_x_y_speed() {
    float degree = 0;

    if (angle >= 90 && angle < 180)
        degree = 180 - angle;
    else if (angle >= 180 && angle < 270)
        degree = angle - 180;
    else if (angle >= 270 && angle <= 360)
        degree = 360 - angle;
    else
        degree = angle;

    float degrees_to_radians = degree*M_PI/180;
    x_speed = speed*cos(degrees_to_radians);
    y_speed = speed*sin(degrees_to_radians);
}

bool Bullet::out_of_range() {
    float x = x_start - item->x();
    float y = y_start - item->y();
    float distance = sqrt(x*x+y*y);

    if (distance > max_range) {
        item->hide();
        return true;
    }
    return false;
}

bool Bullet::collision(QGraphicsPixmapItem *target) {
    if (item->collidesWithItem(target)) {
        item->hide();
        return true;
    }
    return false;
}
