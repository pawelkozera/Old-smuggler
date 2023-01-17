#include "antiaircraftgun.h"

#include <QPainterPath>

/*!Konstruktor wyglądu, cech i działania działek przeciwlotniczych*/
AntiAircraftGun::AntiAircraftGun(QString img_name, Settings *settings, int amount_of_bullets) {
    img.load("../smuggler/assets/enemy/" + img_name);
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

/*!Funkcja sprawdzająca dla działek przeciwlotniczych czy gracz jest w zasięgu ognia*/
bool AntiAircraftGun::is_in_range(QGraphicsPixmapItem *playerPlaneItem) {
    QPointF offset = playerPlaneItem->pos() - item->pos();
    double manhattanL = offset.manhattanLength();

    if (manhattanL <= range) return true;
    return false;
}

/*!Funkcja obracająca działkiem przeciwlotniczym*/
void AntiAircraftGun::rotate(int window_width, int window_height) {
    float x = item->x() - window_width/2;
    float y = -(item->y() - window_height/2);

    int degree = atan2(y, x)*180/M_PI;
    degree = -(degree + 360)%360;

    rotation_angle = degree;
    item->setRotation(degree);
}

/*!Funkcja cech i działania pocisków wystrzeliwanych przez działka przeciwlotnicze*/
void AntiAircraftGun::shoot(QGraphicsPixmapItem *plane, QList<Cloud*> clouds, Sounds *sounds) {
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

                sounds->gun_shot->play();

                break;
            }
        }

        current_delay = 0;
    }
    else {
        current_delay++;
    }
}

/*!Funkcja usuwania pocisków*/
void AntiAircraftGun::move_used_bullets() {
    for (int i = 0; i < used_bullets.size(); i++) {
        if (used_bullets[i]->out_of_range())
            used_bullets.erase(used_bullets.begin() + i);
        else
            used_bullets[i]->move_bullet();
    }
}

/*!Funkcja sprawdzająca kolizje pocisków z graczem i zadawania obrażeń*/
void AntiAircraftGun::check_used_bullets_collision(QGraphicsPixmapItem *target, int *target_hp, bool *target_fuel) {
    bool target_hit = false;
    int chance;
    for (int i = 0; i < used_bullets.size(); i++) {
        target_hit = used_bullets[i]->collision(target);
        if (target_hit) {
            used_bullets.erase(used_bullets.begin() + i);
            if (*target_hp > 0)
                *target_hp = *target_hp - 1;

            chance = rand() % 10;
            if (chance < 2)
                *target_fuel = true;
        }
    }
}

/*!Funkcja sprawdzająca czy gracz jest zasłonięty w chmurach*/
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
