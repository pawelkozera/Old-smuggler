#include "antiaircraftgun.h"

#include <QPainterPath>

AntiAircraftGun::AntiAircraftGun(QString img_name, Settings *settings) {
    img.load("../smuggler/assets/objects/" + img_name);
    range = 740;
    rotation_angle = 0;
    delay = 70;
    current_delay = 0;

    for (int i = 0; i < 5; i++) {
        Bullet *bullet = new Bullet("bullet.png");
        bullet->item = settings->scene->addPixmap(bullet->img);
        bullet->item->setShapeMode(QGraphicsPixmapItem::HeuristicMaskShape);
        bullet->item->setTransformOriginPoint(bullet->img.width()/2, bullet->img.height()/2);
        bullet->item->hide();

        bullets.push_back(bullet);
    }
}

bool AntiAircraftGun::is_in_range(int window_width, int window_height) {
    float x = item->x() - window_width/2;
    float y = item->y() - window_height/2;
    float distance = sqrt(x*x+y*y);

    if (distance <= range) return true;
    return false;
}

void AntiAircraftGun::rotate(int window_width, int window_height) {
    float x = item->x() - window_width/2;
    float y = -(item->y() - window_height/2);

    int degree = atan2(y, x)*180/M_PI;
    degree = -(degree + 360)%360;

    rotation_angle = degree;
    item->setRotation(degree);
}

void AntiAircraftGun::shoot(QGraphicsPixmapItem *plane, QList<Cloud*> clouds) {
    bool bullet_used;
    int x = item->x() + img.width()/2;
    int y = item->y() + img.height()/2;

    if (current_delay >= delay && !is_in_cloud(plane, clouds)) {
        for (int i = 0; i < bullets.size(); i++) {
            bullet_used = std::find(used_bullets.begin(), used_bullets.end(), bullets[i]) != used_bullets.end();
            if (!bullet_used) {
                used_bullets.push_back(bullets[i]);
                bullets[i]->item->show();
                bullets[i]->item->setPos(x, y);
                bullets[i]->set_params(rotation_angle);
                bullets[i]->calculate_x_y_speed();

                break;
            }
        }

        current_delay = 0;
    }
    else {
        current_delay++;
    }
}

void AntiAircraftGun::move_used_bullets() {
    for (int i = 0; i < used_bullets.size(); i++) {
        if (used_bullets[i]->out_of_range())
            used_bullets.erase(used_bullets.begin() + i);
        else
            used_bullets[i]->move_bullet();
    }
}

void AntiAircraftGun::check_used_bullets_collision(QGraphicsPixmapItem *target) {
    bool target_hit = false;
    for (int i = 0; i < used_bullets.size(); i++) {
        target_hit = used_bullets[i]->collision(target);
        if (target_hit)
            used_bullets.erase(used_bullets.begin() + i);
    }
}

bool AntiAircraftGun::is_in_cloud(QGraphicsPixmapItem *plane, QList<Cloud *> clouds)
{
    for (Cloud* cloud : clouds)
    {
        if (plane->collidesWithItem(cloud->cloudPixmap))
        {
           return true;
        }
    }
    return false;
}
