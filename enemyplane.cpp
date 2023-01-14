#include "enemyplane.h"

EnemyPlane::EnemyPlane(QString img_name, Settings *settings, int amount_of_bullets) : AntiAircraftGun(img_name, settings, amount_of_bullets) {
    speed = 2;
    range = 1200;
    index = 0;
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

    for (int i = 0; i < x_points.size(); i++) {
        x_points[i] += x_speed;
    }

    for (int i = 0; i < y_points.size(); i++) {
        y_points[i] += y_speed;
    }

    item->setPos(plane_x + x_speed, plane_y + y_speed);
}

void EnemyPlane::follow_player(int window_width, int window_height, PlayerPlane *playerPlane) {
    QPointF offset = playerPlane->item->pos() - item->pos();
    double manhattanL = offset.manhattanLength();

    if (manhattanL != 0) {
        offset = offset / manhattanL;
        if (manhattanL < 600 && manhattanL > 300) {
            item->setPos(item->pos() + offset);
        }
        else if (manhattanL >= 600 && manhattanL <= 900) {
            item->setPos(item->pos() + offset * 2);
        }
        else if (manhattanL > 900) {
            item->setPos(item->pos() + offset * 4);
        }
    }
}

void EnemyPlane::move_to_point() {
    QPointF destination = QPointF(x_points[index], y_points[index]);
    QPointF currentPos = item->pos();
    QVector2D offset(destination - currentPos);
    qreal distance = offset.length();

    if(distance > speed) {
        offset.normalize();
        offset *= speed;
        item->setPos(currentPos + offset.toPointF());

        double angle = atan2(destination.y() - item->y(), destination.x() - item->x()) * 180 / M_PI;
        item->setRotation(angle - 180);
    }
    else {
        if (index >= x_points.size() - 1) index = 0;
        else index++;
        item->setPos(destination);
    }
}
