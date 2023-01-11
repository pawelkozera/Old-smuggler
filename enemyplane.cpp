#include "enemyplane.h"

EnemyPlane::EnemyPlane(QString img_name, Settings *settings, int amount_of_bullets) : AntiAircraftGun(img_name, settings, amount_of_bullets) {
    speed = 2;
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

void EnemyPlane::follow_player(int window_width, int window_height, PlayerPlane *playerPlane) {
    QPointF offset = playerPlane->item->pos() - item->pos();
    double manhattanL = offset.manhattanLength();

    if (manhattanL != 0) {
        if (manhattanL < 300) {
            offset = offset / manhattanL;
            item->setPos(item->pos() + offset);
        }
        else if (manhattanL >= 450 && manhattanL <= 600) {
            offset = offset / manhattanL;
            item->setPos(item->pos() + offset * 2);
        }
        else if (manhattanL > 600 && manhattanL <= 800) {
            offset = offset / manhattanL;
            item->setPos(item->pos() + offset * 3);
        }
        else if (manhattanL > 800 && manhattanL <= 1200) {
            offset = offset / manhattanL;
            item->setPos(item->pos() + offset * 4);
        }
    }
}

void EnemyPlane::move_to_point() {}
