#include "island.h"
#include "movingspeed.h"

#include <QDebug>
#include <QKeyEvent>


Island::Island(QString img_name) {
    target_island = false;
    island_img.load("../smuggler/assets/map/" + img_name);
}

void Island::move_island_event(QKeyEvent *event, long double x_speed, long double y_speed) {
    if (event->key() == Qt::Key_A) {
        move_island(x_speed, 0);
    }
    else if (event->key() == Qt::Key_D) {
        move_island(-x_speed, 0);
    }
    else if (event->key() == Qt::Key_W) {
        move_island(0, y_speed);
    }
    else if (event->key() == Qt::Key_S) {
        move_island(0, -y_speed);
    }
}

void Island::move_island(long double x_speed, long double y_speed) {
    float island_x = island_item->x();
    float island_y = island_item->y();

    island_item->setPos(island_x + x_speed, island_y + y_speed);
    move_objects_on_island(x_speed, y_speed);
}

void Island::move_objects_on_island(long double x, long double y) {
    for (int i = 0; i < objects.size(); i++) {
        objects[i]->move_object(x, y);
    }
}
