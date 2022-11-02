#include "island.h"
#include "movingspeed.h"

#include <QDebug>
#include <QKeyEvent>


Island::Island(int x, int y, QString img_name) {

    is_visible = false;
    island_img.load("../smuggler/assets/map/" + img_name);
    borders = QRect(x, y, island_img.width(), island_img.height());
    set_last_position(0, "");
}

QRectF Island::boundingRect() const {
    // outer most edges
    return borders;
}

void Island::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    //painter->drawPixmap(borders, island_img);
}

void Island::move_island(QKeyEvent *event) {
    int x_speed = MovingSpeed::x_speed;
    int y_speed = MovingSpeed::y_speed;
    int island_x = island_item->x();
    int island_y = island_item->y();

    if (event->key() == Qt::Key_A) {
        island_item->setPos(island_x + x_speed, island_y);
        set_last_position(island_x + x_speed, "a");
    }
    if (event->key() == Qt::Key_D) {
        island_item->setPos(island_x - x_speed, island_y);
        set_last_position(island_x - x_speed, "d");
    }
    if (event->key() == Qt::Key_W) {
        island_item->setPos(island_x, island_y + y_speed);
        set_last_position(island_y, "w");
    }
    if (event->key() == Qt::Key_S) {
        island_item->setPos(island_x, island_y - y_speed);
        set_last_position(island_y, "s");
    }
}

void Island::set_last_position(int position, QString direction) {
    last_position = position;
    last_direction = direction;
}

void Island::move_to_the_last_position() {
    int x = island_item->x();
    int y = island_item->y();
    int pixels_to_move = 8;

    if (last_direction == "a") {
        island_item->setPos(last_position - pixels_to_move, y);
    }
    else if (last_direction == "d") {
        island_item->setPos(last_position + pixels_to_move, y);
    }
    else if (last_direction == "w") {
        island_item->setPos(x, last_position - pixels_to_move);
    }
    else if (last_direction == "s") {
        island_item->setPos(x, last_position + pixels_to_move);
    }
}

bool Island::collision_with_player(QGraphicsPixmapItem *player_character) {
    if (player_character->collidesWithItem(island_item, Qt::ContainsItemShape))
        return true;
    return false;
}
