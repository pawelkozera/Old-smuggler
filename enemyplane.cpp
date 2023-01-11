#include "enemyplane.h"

EnemyPlane::EnemyPlane(QString img_name, Settings *settings, int amount_of_bullets) : AntiAircraftGun(img_name, settings, amount_of_bullets) {
}

void EnemyPlane::move_plane_event(QKeyEvent *event, long double x_speed, long double y_speed) {
    if (event->key() == Qt::Key_A) {
        move_plane(x_speed, 0);
    }
    else if (event->key() == Qt::Key_D) {
        move_plane(-x_speed, 0);
    }
    else if (event->key() == Qt::Key_W) {
        move_plane(0, y_speed);
    }
    else if (event->key() == Qt::Key_S) {
        move_plane(0, -y_speed);
    }
}

void EnemyPlane::move_plane(long double x_speed, long double y_speed) {
    float plane_x = item->x();
    float plane_y = item->y();

    item->setPos(plane_x + x_speed, plane_y + y_speed);
}

void EnemyPlane::follow_player() {}
