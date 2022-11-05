#include "playerplane.h"
#include "movingspeed.h"

#include <QKeyEvent>


PlayerPlane::PlayerPlane(int x, int y) {
    current_index_of_plane_img = 0;

    QPixmap plane_img;
    for (int i = 1; i <= 3; i++) {
        QString location = "../smuggler/assets/player_plane/plane" + QString::number(i) + QString(".png");
        plane_img.load(location);
        imgs.push_back(plane_img);
    }

    setPos(x, y);
}

void PlayerPlane::simple_movement(QKeyEvent *event) {
    int x_speed = MovingSpeed::x_speed;
    int y_speed = MovingSpeed::y_speed;
    int plane_x = item->x();
    int plane_y = item->y();

    if (event->key() == Qt::Key_A) {
        item->setPos(plane_x + x_speed, plane_y);
    }
    if (event->key() == Qt::Key_D) {
        item->setPos(plane_x - x_speed, plane_y);
    }
    if (event->key() == Qt::Key_W) {
        item->setPos(plane_x, plane_y + y_speed);
    }
    if (event->key() == Qt::Key_S) {
        item->setPos(plane_x, plane_y - y_speed);
    }
}
